# docker使用入门（二）：容器container
docker层次结构可以分为三层，从下往上是：容器（container）、服务（services）、堆栈（stack），其中services定义了容器的行为，stack  定义了services的交互   
接下来是尝试如何使用docker在容器中启动一个应用程序
## 创建容器
1. 创建一个空的文件夹，其中包含Dockerfile、app.py、requirements.txt三个文件，文件内容分别如下

Dockerfile
```bash
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

requirements.txt
```
Flask
Redis
```

app.py
```python
from flask import Flask
from redis import Redis, RedisError
import os
import socket

# Connect to Redis
redis = Redis(host="redis", db=0, socket_connect_timeout=2, socket_timeout=2)

app = Flask(__name__)

@app.route("/")
def hello():
    try:
        visits = redis.incr("counter")
    except RedisError:
        visits = "<i>cannot connect to Redis, counter disabled</i>"

    html = "<h3>Hello {name}!</h3>" \
           "<b>Hostname:</b> {hostname}<br/>" \
           "<b>Visits:</b> {visits}"
    return html.format(name=os.getenv("NAME", "world"), hostname=socket.gethostname(), visits=visits)

if __name__ == "__main__":
```

## 构建应用程序
使用以下命令build镜像
```bash
docker build --tag=friendlyhello  .
# or  docker build -t=friendlyhello  .
```
使用`docker image ls`可以查看构建的image
```bash
 $  docker image ls
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
friendlyhello       latest              7ecc82fd960a        53 minutes ago      148MB
python              2.7-slim            5f759d36aead        7 hours ago         137MB
hello-world         latest              fce289e99eb9        7 months ago        1.84kB

```
其中TAG默认为`latest`，可以使用`--tag=friendlyhello:v0.0.1.`来指定tag
## 运行应用程序
使用以下语句运行程序
```bash
docker run -p 4000:80 friendlyhello
```
其中`-p 4000:80` 表示将image的80端口映射到主机的4000端口。
运行`http://localhost:4000`可以查看程序运行结果  
使用`-d`可以让程序后台运行
```bash
$ docker run -d -p 4000:80 friendlyhello
c21b81020e77e9f15df5fafbfdaf2791599c6233b4169615ea9226f243ff68b8

$ docker container ls
CONTAINER ID        IMAGE               COMMAND             CREATED              STATUS              PORTS                  NAMES
c21b81020e77        friendlyhello       "python app.py"     About a minute ago   Up About a minute   0.0.0.0:4000->80/tcp   elegant_raman

# 关闭程序
$ docker container stop c21b

$ docker container ls
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
```

## 共享iamge

### 登录账户

我们可以将image上传到dockerhub中，从而能够在任何地方运行image。    
首先我们需要先[注册](hub.docker.com)一个账号，然后输入`docker login`在本地登录账号   

### 使用镜像加速器
直接访问dockerhub时，访问速度会较慢，这时候可以采用镜像加速器。国内的镜像加速器有
- Azure 中国镜像 https://dockerhub.azk8s.cn
- 七牛云加速器 https://reg-mirror.qiniu.com
- [阿里云加速器(需登录账号获取)](https://cr.console.aliyun.com/cn-hangzhou/mirrors)

在`/etc/docker/daemon.json`中写入以下内容

```bash
{
  "registry-mirrors": [
    "https://dockerhub.azk8s.cn",
    "https://reg-mirror.qiniu.com"
  ]
}
```

之后重启服务
```bash
$ sudo systemctl daemon-reload
$ sudo systemctl restart docker
```

执行`docker info`可以查看镜像是否添加成功
```
$ docker info
   ...
 Registry Mirrors:
  https://dockerhub.azk8s.cn/
  https://reg-mirror.qiniu.com/
 Live Restore Enabled: false

```
### 关联仓库

使用`username/repository:tag`可已将本地image和远程仓库关联到一起，其中`tag`是可选的，当`tag`时，仓库会为相应的image打上标签。其完整的指令是
```bash
docker tag image username/repository:tag
```

例如

```bash
docker tag friendlyhello   yezh01/getstart:v1.0

$ docker image ls
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
friendlyhello       latest              7ecc82fd960a        23 hours ago        148MB
yezh01/getstart     v1.0                7ecc82fd960a        23 hours ago        148MB
python              2.7-slim            5f759d36aead        30 hours ago        137MB
hello-world         latest              fce289e99eb9        7 months ago        1.84kB
```
检查image可以发现其中多了一个yezh01/getstart

###　上推image

我们需要先将image上传到dockerhub中，才能在不同机器上运行image，上传指令为：
```
$ docker push yezh01/getstart:v1.0 
```

上传完成后，，我们可以通过在任何机器上通过以下命令运行image
```bash
docker run -p 4000:80 username/repository:tag
```
系统执行以上指令时，首先会在本地找相应的image，若本地不存在则会自动尝试从dockerhub中获取image，因此无论我们可以方便的在不同机器上部署开发docker

## 相关命令
```bash
docker build -t friendlyhello .  # Create image using this directory's Dockerfile
docker run -p 4000:80 friendlyhello  # Run "friendlyhello" mapping port 4000 to 80
docker run -d -p 4000:80 friendlyhello         # Same thing, but in detached mode
docker container ls                                # List all running containers
docker container ls -a             # List all containers, even those not running
docker container stop <hash>           # Gracefully stop the specified container
docker container kill <hash>         # Force shutdown of the specified container
docker container rm <hash>        # Remove specified container from this machine
docker container rm $(docker container ls -a -q)         # Remove all containers
docker image ls -a                             # List all images on this machine
docker image rm <image id>            # Remove specified image from this machine
docker image rm $(docker image ls -a -q)   # Remove all images from this machine
docker login             # Log in this CLI session using your Docker credentials
docker tag <image> username/repository:tag  # Tag <image> for upload to registry
docker push username/repository:tag            # Upload tagged image to registry
docker run username/repository:tag                   # Run image from a registry
```
## 相关链接
https://docs.docker.com/get-started/part2/