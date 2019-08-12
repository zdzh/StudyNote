# docker学习三：network

docker支持容器之间的网络通信，docker的网络通信方式有以下五种：   
|         |                   |                          |
| ------- | ------------ | --------------- |
| bridge  | docker 默认的网络驱动，如果不指定网络驱动，docker就会创建一个bridge                                            | bridge适用于同一docker主机上的容器通信                                         |
| overlay | overlay支持不同daemon下的容器之间和集群服务之间的相互通信                                                      | overlay适用于不同主机的容器之间的通信，或者集群服务中的多个应用程序协调工作    |
| host    | host消除了独立容器与主机之间的网络隔离，container直接使用主机的网络                                            | host适用于需要隔离容器除网络以外的其他部分的情况                               |
| macvlan | macvlan允许用户为容器分配MAC地址，daemon可以将流量通过容器MAC地址之间路由到容器而不需要经过docker host的网络栈 | macvlan适用于从虚拟机配置移植或者需要让容器表现为一台包含mac地址的物理机的情况 |
| none    | none禁止容器的所有网络，其一般和用户自定义网络驱动一起使用，集群服务不支持none                                 |

## bridge
docker bridge与一般的网桥功能类似，能够让同一网桥下的容器相互通信。  
docker提供默认bridge，若不指定容器的驱动，则自动将容器关联到默认bridge中。     官方推荐用户自定义bridge而不是使用默认bridge
### 自定义bridge和默认bridge的区别
|                   | 自定义bridge                                                                     | 默认bridge                                              |
| ----------------- | --- | ---------------------- |
| 隔离性和连接性    | 位于同一bridge的容器之间暴露自身所有的端口，容器端口默认对外界关闭，需要使用`-p`或`--publish`开启| 需要手动打开端口，同时需要通过docker外的方式控制外界对端口的访问  |
| 容器之前的DNS服务 | 支持自动DNS解析，可以通过容器别名访问容器         | 容器之间只能通过ip地址访问或者为通信两端的容器分别使用`--link`选项                         |
| 热插拔            | 支持在运行过程中断开或连接自定义bridge                                           | 容器与默认网桥断开时，需要关闭容器并使用新配置重建容器                         |
| 全局配置          | 每个自定义bridge可以使用docker命令单独配置                                       | 对默认bridge的配置会影响到所有使用默认bridge的容器，且配置默认bridge需要使用docker外的命令 |
| 共享环境变量      | 自定义bridge无法直接共享环境变量，但可以通过<br> 挂载卷或者目录<br>  使用compos声明共享变量<br>使用集群服务代替独立容器，通过配置共享变量  |使用`--link` flag共享环境变量

### 配置自定义bridge
创建和删除bridge的命令如下：

```bash
docker network create my-net
docker network rm my-net
```

创建bridge时可以配置bridge的子网范围、网关和其他选项，具体的配置参数可以使用`docker network --help`或者查看[官方文档](https://docs.docker.com/engine/reference/commandline/network_create/#specify-advanced-options)  


### 连接bridge

可以在创建容器的同时连接bridge，如：
```bash
$ docker create --name my-nginx \
  --network my-net \
  --publish 8080:80 \
  nginx:latest

  $ docker container ls -a
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS                    PORTS               NAMES
a716400c6714        nginx:latest        "nginx -g 'daemon of…"   7 minutes ago       Created                                       my-nginx
```

上面创建了一个容器my-nginx，同时将容器连接到my-net 网桥并将8080端口暴露出来供外界访问。   
连接已存在的容器和bridge时可以使用以下命令
```bash
$ docker network connect my-net my-nginx
```

取消连接可以使用以下命令
```bash
$ docker network disconnect my-net my-nginx
```

## overlay
overlay在多个docker主机上面创建一个分布式网络，该网络位于各个主机的具体网络之上，允许容器连接该网络进行通信。   
当创建一个集群或者将docker主机加入到集群时，docker主机会创建两个网络：   
1.  `ingress`：是一个overlay网络，用于处理和集群控制有关的命令和数据流量，如果创建集群时没有指定自定义overlay网络，集群默认连接到`ingress`
2.  `docker_gwbridge`：一个 bridge网络，用于连接集群中各个daemon守护进程

### 创建overlay

创建overlay的命令与bridge基本一致，但创建overlay的命令必须在位于集群中的主机执行，使用命令`docker swarm init`或 `docker  swarm join`将主机加入到集群中

```bash
$ docker network create -d overlay my-overlay
```

## host
使用host网络相当于容器和主机共享一个网络，docker不会为容器分配ip地址，访问容器端口的方式改为直接访问主机对应的端口，`-p`、`-P`等端口相关的指令会被忽略。   
host网络只在linux下工作，不提供对mac和Windows的支持

## macvlan

某些应用程序，尤其是后台应用程序或监视网络流量的应用程序，希望直接连接到物理网络。在这种情况下，您可以使用macvlan网络驱动程序为每个容器的虚拟网络接口分配MAC地址，使其看起来像是直接连接到物理网络的物理网络接口。在这种情况下，您需要在Docker主机上指定一个物理接口，用于macvlan，以及macvlan的子网和网关。您甚至可以使用不同的物理网络接口隔离您的macvlan网络。但需要记住以下事项：
- 由于IP地址耗尽或“VLAN传播”，很容易无意中损坏您的网络，在这种情况下，网络中存在大量不合适的MAC地址。
- 您的网络设备需要能够处理“混杂模式”，其中一个物理接口可以分配多个MAC地址。 
- 如果您的应用程序可以使用bridge（在单个Docker主机上）或overlay（跨多个Docker主机进行通信），那么从长远来看，这些解决方案可能会更好。

## none：关闭容器的网络

使用`--network none`可以关闭容器内的网络栈，在容器内只剩下回环地址。
```bash
$ docker run --rm -dit \
  --network none \
  --name no-net-alpine \
  alpine:latest \
  ash
```

查看容器内部网络，里面只含有回环地址
```bash
$ docker exec no-net-alpine ip link show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```