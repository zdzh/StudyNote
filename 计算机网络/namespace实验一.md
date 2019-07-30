# Net namespace实验
  在 Linux 中，网络名字空间可以被认为是隔离的拥有单独网络栈（网卡、路由转发表、iptables）的环境。网络名字空间经常用来隔离网络设备和服务，只有拥有同样网络名字空间的设备，才能看到彼此。 network namespace 是实现网络虚拟化的重要功能，它能创建多个隔离的网络空间，它们有独自的网络栈信息。不管是虚拟机还是容器，运行的时候仿佛自己就在独立的网络中

## 常用命令
| comm               | 命令               |
| :----------------- | :----------------- |
| ip netns add  net1 | 添加namespace net1 |
|ip netns help |获取帮助|
|ip netns del n1| 删除namespace n1|
|ip netns ls|列出当前已有namespace|
与net namespace相关的指令是`ip netns`后面跟具体指令  
使用`ip netns exec   name`子命令后面可以加上任何命令，表示在相应的namespace中执行相关命令，如：
```bash
root@mininet-vm:/home/mininet# ip netns exec n2 ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```
可以执行`ip netns exec n2 bash`，之后所有指令都在指定namespace中执行而不需要加上`ip netns exec   name`
```bash
root@mininet-vm:/home/mininet# ip netns exec n2 ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
root@mininet-vm:/home/mininet# ip netns exec n2 bash
root@mininet-vm:/home/mininet# ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
root@mininet-vm:/home/mininet# exit
exit
root@mininet-vm:/home/mininet# ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast 
.................
```
使用`ip netns exec n2 bash  --rcfile <(echo "PS1=\"namespace ns1>\"")`可以修改命令行的前缀。
```bash
root@mininet-vm:/home/mininet# ip netns exec n2 bash --rcfile <(echo "PS1=\"namespace n2>\"")
namespace n2>
```
##　namespace通信
### 使用 veth pair 进行通信
1. 创建一对veth pair   
   使用命令`ip link add type veth`创建一对veth pair，其默认名是veth0和veth1，使用`ip link`可查看链接
```bash
   root@mininet-vm:/home/mininet# ip link
.....
3: ovs-system: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN 
root@mininet-vm:/home/mininet # ip link add type veth
root@mininet-vm:/home/mininet # ip link
....
3: ovs-system: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN 
9: veth0@veth1: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 12:e8:a5:43:c0:43 brd ff:ff:ff:ff:ff:ff
10: veth1@veth0: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 9e:f8:c3:b9:af:ec brd ff:ff:ff:ff:ff:ff
```
2. 将veth pair的两端分别放到两个namespace   
   使用命令`ip link set veth0 netns n1`和`ip link set veth1 netns n2`分别将veth0和veth1放到不同namespace
```bash
oot@mininet-vm:/home/mininet# ip link set veth0 netns n1
root@mininet-vm:/home/mininet# ip link set veth1 netns n2
root@mininet-vm:/home/mininet# ip netns exec n1 ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
9: veth0@if10: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 12:e8:a5:43:c0:43 brd ff:ff:ff:ff:ff:ff
root@mininet-vm:/home/mininet# ip netns exec n2 ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
10: veth1@if9: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 9e:f8:c3:b9:af:ec brd ff:ff:ff:ff:ff:ff
```
3. 为veth pair的两端分别配置ip
   使用命令`ip link set vethX up`和`ip addr add  10.0.0.10/24 dev vethX`为veth pair配置ip，结果如下
```bash
# namespace 1
namespace ns1> ip link set veth0 up
namespace ns1> ip a
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
9: veth0@if10: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 12:e8:a5:43:c0:43 brd ff:ff:ff:ff:ff:ff
namespace ns1> ip addr add 10.0.10.1/24 dev veth0
namespace ns1> ip a
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
9: veth0@if10: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 12:e8:a5:43:c0:43 brd ff:ff:ff:ff:ff:ff
    inet 10.0.10.x1/24 scope global veth0
       valid_lft forever preferred_lft forever

# namespace 2
namespace n2>ip link set veth1 up
namespace n2>ip addr add 10.0.10/24 dev veth1
namespace n2>ip a
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
10: veth1@if9: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast state LOWERLAYERDOWN group default qlen 1000
link/ether 9e:f8:c3:b9:af:ec brd ff:ff:ff:ff:ff:ff
    inet 10.0.10.0/24 scope global veth1
       valid_lft forever preferred_lft forever
```
   4. 测试两个namespace之间的网络联通状态
   分别在n1和n2中尝试ping
```bash
namespace ns1> ping 10.0.10.0 -c 1
PING 10.0.10.0 (10.0.10.0) 56(84) bytes of data.
64 bytes from 10.0.10.0: icmp_seq=1 ttl=64 time=0.035 ms
namespace n2>ping 10.0.10.1 -c 1
PING 10.0.10.1 (10.0.10.1) 56(84) bytes of data.
64 bytes from 10.0.10.1: icmp_seq=1 ttl=64 time=0.040 ms
```
5. 其拓扑结构如下  
   ![20190725185608.png](https://raw.githubusercontent.com/zdzh/pothos/master/img/20190725185608.png)    
*veth pair可以用于两个namespace之间的通信，但不适合用在多个namespace之间的通行*
### 利用bridge通信
1. 在以上实验基础上，重新创建两个namespace：n3、n4
```bash
root@mininet-vm:/home/mininet# ip netns add n3
root@mininet-vm:/home/mininet# ip netns add n4
root@mininet-vm:/home/mininet# ip netns ls
n4
n3
n1
n2
```
2. 创建bridge
```bash
root@mininet-vm:/home/mininet# ip link add br0 type bridge
root@mininet-vm:/home/mininet# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 00:0c:29:1e:27:79 brd ff:ff:ff:ff:ff:ff
    inet 192.168.117.128/24 brd 192.168.117.255 scope global eth0
       valid_lft forever preferred_lft forever
3: ovs-system: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default 
    link/ether 72:f5:e5:5d:4d:ed brd ff:ff:ff:ff:ff:ff
11: br0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default 
    link/ether 76:d8:06:1a:b9:84 brd ff:ff:ff:ff:ff:ff
```
3. 利用veth pair将bridge与n3、n4、n1连通
   创建3对veth pair
```bash
root@mininet-vm:/home/mininet# ip link add type veth
root@mininet-vm:/home/mininet# ip link add type veth
root@mininet-vm:/home/mininet# ip link add type veth
root@mininet-vm:/home/mininet# ip a
...
11: br0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default 
    link/ether 76:d8:06:1a:b9:84 brd ff:ff:ff:ff:ff:ff
12: veth0@veth1: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether ea:98:b6:3c:46:60 brd ff:ff:ff:ff:ff:ff
13: veth1@veth0: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether f2:f6:d8:6b:31:1f brd ff:ff:ff:ff:ff:ff
14: veth2@veth3: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 4a:7d:af:18:67:14 brd ff:ff:ff:ff:ff:ff
15: veth3@veth2: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether ca:b6:e4:eb:b7:15 brd ff:ff:ff:ff:ff:ff
16: veth4@veth5: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether f2:b3:5f:0e:3d:09 brd ff:ff:ff:ff:ff:ff
17: veth5@veth4: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 76:0c:87:b1:16:80 brd ff:ff:ff:ff:ff:ff
```
  将br0和n1，n3，n4连接  
  这时候如果把veth0加入n1的话会报错，因为n1里面已经有了一个veth0，可以换成其他名称的veth。
将veth pair放如br0的指令为`ip link set dev veth3 master br0`
4. 测试n1-n4之间的连通状态
   发现不同namespace之间无法ping通 。   
   这个问题折腾了很久，后来多配置了几次有可以了。应该是之前漏掉了几个步骤，完整的步骤应该包括以下几步：
   ```bash
   # 启动网桥（网桥只需要启动一次就行）
   ip link set br0 up
   # 创建vethpair
   ip link add br-1 type veth peer name 1-br
   #将vethpair分配给网桥和namespace
   ip link set br-1 master br0
   ip link set 1-br netns n1
   #启动veth
   ip link set br-1 up
   ip netns exec n1 ip link set 1-br up
   # 为namespace中的veth设置ip
  ip netns exec n1 ip addr add 10.0.10.2/24 dev 1-br
   ```
重新测试，发现三个namespace可以相互ping通。
*上述网桥对应的veth的ip其实可以省略*

5. 其拓扑结构如下
![](https://raw.githubusercontent.com/zdzh/pothos/master/img/!%5B20190726101019.png%5D(httpsraw.githubusercontent.comzdzhpothosmasterimg20190726101019.png))



 ### namespace内部与namespace外部通信
默认情况下，namespace网络是隔离的，namespace内无法ping通namespace外的网络，可以通过veth pair打通网络状态。
当veth pair一端在namespace内部，一端在namespace外部时，namespace可以ping通位于外部的veth pair但无法ping同其他网络。
## 参考资料
> https://cizixs.com/2017/02/10/network-virtualization-network-namespace/