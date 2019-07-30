
# namespace实验二

在之前的实验的基础上增加namespace对外部网络的支持。
在之前的实验中，namespace是无法ping通主机的网卡地址的。
## 添加默认路由
### 路由表
所有的命名空间都含有一个路由表。使用`route`可以查看路由表信息，以下是n1的路由表信息：
```bash
namespace ns3>route
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
10.0.10.0                  *                  255.255.255.0   U     0      0        0 3-br
```
Destination是目的地址，Gateway是网关，Genmask是子网掩码，Use Iface代表下一跳传入的地址
这里的意思是目的地址10.0.10.0网段的请求都通过3-br转发出去。
### 设置默认路由
默认路由的目的地址是0.0.0.0，当进行路由匹配时，首先会匹配明细路由，在匹配默认路由，也就是说，当路由表中存在匹配度高的选项时优先匹配，若无匹配的选项则发到默认路由
```bash
namespace ns3>route add -net default gw 10.0.10.7 dev 3-br
namespace ns3>route
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
default         10.0.10.7       0.0.0.0         UG    0      0        0 3-br
10.0.10.0       *               255.255.255.0   U     0      0        0 3-br
```
上面添加了一个默认路由/网关，表示将所有的ip请求发送到3-br。
这时候尝试ping主机地址，可以发现能够连通
```bash
namespace ns3>ping 192.168.117.128
PING 192.168.117.128 (192.168.117.128) 56(84) bytes of data.
64 bytes from 192.168.117.128: icmp_seq=1 ttl=64 time=0.065 ms
```
用同样的方法为所有namespace设置默认路由即可连接主机网络。
尝试ping外部的网络，发现还是ping不同，需要做进一步处理
## 设置NAT
使用以下命令设置snat
```bash
 sudo iptables -t nat -A POSTROUTING -s 10.0.10.0/24 -o vmnet8 -j MASQUERADE
```
其中POSTROUTING表示在路由选择之后进行，10.0.10.0/24 -代表源地址网段，vmnet8代表 出口，MASQUERADE表示需要做sna处理
使用以下命令行可以控制已添加的nat
```bash
sudo  iptables -t nat -vnL POSTROUTING --line-number    # 查看nat表
sudo iptables -t nat -D POSTROUTING 1   # 删除第一条nat规则
```
进行以上步骤后再ping外网ip还是无法连通
##设置路由转发
将数据传递给网卡后，网卡需要开启转发功能才能充当路由。使用以下命令可以查看转发功能是否打开
```bash
$ cat /proc/sys/net/ipv4/ip_forward
0   #0 表示未打开
```
使用命令`# echo 1 > /proc/sys/net/ipv4/ip_forward`打开该功能，*注意该命令需要root账户运行*
## 使用veth pair连接网桥和主机网络
1. 使用`ip  link add br-h type peer name h-br`创建一对veth pair
2. 使用`ip link set  br-h master br0`将br-h放到br0中
3. 使用一下指令配置veth pair