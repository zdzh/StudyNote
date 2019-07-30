# docker(三)：服务services
docker中services位于container上面，services可以控制image的运行方式，包括image运行时所需资源的大小

## 创建yml文件
yml文件定义了容器运行时的行为。我们先创建一个`docker-compose.yml`文件，其包含以下内容

```yml
version: "3"
services:
  web:
    # replace username/repo:tag with your name and image details
    image: username/repo:tag
    deploy:
      replicas: 5
      resources:
        limits:
          cpus: "0.1"
          memory: 50M
      restart_policy:
        condition: on-failure
    ports:
      - "4000:80"
    networks:
      - webnet
networks:
  webnet:
```

其中，各个字段含义如下
-` image`是容器仓库的名字 
- `replicas`表示生成的实例个数，上述表示5个实例
- `cpus`表示占用cpu的时间，上述表示每个实例占用单核cpu10%的运行时间
- `memory`表示占用内存大小
- ` condition: on-failure`表示当一个实例故障时，重启容器
- `ports`将主机的4000端口映射到web的80端口
- `network`使用默认设置配置webnet

## 运行服务
执行以下指令运行服务

```bash
docker swarm init
docker stack deploy -c docker-compose.yml  hello
```
其中hello是自行设置的应用程序名

使用以下命令可以获取服务id
```bash
 $ docker service  ls
ID                  NAME                MODE                REPLICAS            IMAGE                  PORTS
kv6p22irsbds        hello_web           replicated          5/5                 friendlyhello:latest   *:4000->80/tcp

#or
$ docker stack services hello
ID                  NAME                MODE                REPLICAS            IMAGE                  PORTS
kv6p22irsbds        hello_web           replicated          5/5                 friendlyhello:latest   *:4000->80/tcp
```

使用以下命令可以获得各个实例的信息
```bash
$ docker stack ps hello
ID                  NAME                IMAGE                  NODE                DESIRED STATE       CURRENT STATE            ERROR               PORTS
g77x3nxbyeim        hello_web.1         friendlyhello:latest   pc                  Running             Running 25 minutes ago                       
a329cldr272o        hello_web.2         friendlyhello:latest   pc                  Running             Running 25 minutes ago                       
zr8putqyx4nd        hello_web.3         friendlyhello:latest   pc                  Running             Running 25 minutes ago                       
x7cun5z3kuu3        hello_web.4         friendlyhello:latest   pc                  Running             Running 25 minutes ago                       
kc5lb0ni8y5k        hello_web.5         friendlyhello:latest   pc                  Running             Running 25 minutes ago        
```

## 拓展应用程序
docker支持即时更新部署，可以在运行时更新应用程序而无需停止服务，更新语句与运行语句一致
```bash
docker stack deploy -c docker-compose.yml hello
```

## 关闭应用程序
```bash
docker stack rm hello
docker swarm leave --force
```

##相关命令
```bash
docker stack ls                                            # List stacks or apps
docker stack deploy -c <composefile> <appname>  # Run the specified Compose file
docker service ls                 # List running services associated with an app
docker service ps <service>                  # List tasks associated with an app
docker inspect <task or container>                   # Inspect task or container
docker container ls -q                                      # List container IDs
docker stack rm <appname>                             # Tear down an application
docker swarm leave --force      # Take down a single node swarm from the manager
```