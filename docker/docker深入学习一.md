# docker 理解

docker是一个客户服务器结构的应用程序，其结构如下所示 

![](assets/2019-07-31-14-58-36.png)  

其组成部分包括

- container容器：是image的运行实例，一般container之间以及container与主机之间是相互隔离的，相当于一台轻量级的虚拟机
- iamge镜像：是一个只读模板，是静态的，image通常是给予另一个image创建的
- docker CLI 客户端：通过调用RESTAPI控制docker daemon
- RESTAPI：是与docker daemon交互的API
- docker daemon守护进程 ：docker daemon是一个始终运行的守护进程
- network
- datavolumes


## dockerfile
dockerfile是一个包含生成image所需命令的文本文件，使用`docker build`可以自动生成image。  

Dockerfile文件是以`FROM`开头的，也就是说必须引用一个base image如下所示

```dockerfile
# 使用python的运行环境作为parent image
FROM python:2.7-slim

# 设置工作路径
WORKDIR /app

# 将当前目录的内容复制到相应路径下
COPY . /app

# 下载requirements.txt中要求的包
RUN pip install --trusted-host pypi.python.org -r requirements.txt

# 暴露容器的80端口
EXPOSE 80

# 定义环境变量
ENV NAME World

#当docker开始运行时执行文件
CMD ["python", "app.py"]
```

`docker build`后面可以接本地地址`PATH`也可以使用远程地址`URL`，如
```bash
$ docker build .
```
实际 执行`build`指定的是daemon而不是CLI（CLI相当输入命令行的shell），也就是说输入`docker build`后，cli会将命令连同上下文环境一起发送给daemon，  `docker build`后面接的`PATH`或者`URL`就是上下文环境。  
**注意**：不要将`\`目录作为上下文环境，因为docker会将上下文环境下的所有文件和文件夹递归发送给daemon。 推荐的做法是新建一个空目录作为上下文环境  

类似于github的`.gitignore`文件，docker也可以使用`.dockerignore`来忽略指定文件和目录

`docker build`后面的`PATH`并不代表的dockerfile所在的路径，但默认情况下docker会在`PATH`中寻找Dockerfile，如果要指定dockerfile ，可以使用参数`-f`，如

```bash
docker build -f /path/dockerfile   .
```

使用参数`-t`可以可以指定生成image的仓库名称和标签，如
```bash
docker  build  -t yezh01/getstart .
# 　在仓库名称后面可以添加不同标签，同时build命令后面可以接多个 -t 参数
docker  build  -t yezh01/getstart:v1.1  -t yezh01/getstart:latest .
```

## image
image是根据Dockerfile生成的由多个只读层组成的。对于下面的dockerfile，每条命令生成一个只读层

```dockerfile
FROM ubuntu:18.04
COPY . /app
RUN make /app
CMD python /app/app.py
```
其一共生成四个层次：
- FROM 根据ubuntu:18.04生成一个层次
- copy将运行docker命令的目录下的文件复制到容器中的app文件中
- run 使用make命令生成应用程序
- cmd 在容器中运行指定命令


## container
container是根据image生成的运行实例，与image相比，container在image层次的基础上增加了一层读写层。所有对container的操作，例如增加、删除、修改文件等操作都会写入读写层。