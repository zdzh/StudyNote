# mininet：vxlan实验

## 需改虚拟机的网络适配器，将其改为host-only  

 尝试ping宿主机ip地址，此时能够ping同与虚拟机相连的虚拟网卡ip地址，无法ping同其他网卡ip地址
## 在虚拟机和宿主机中创建网络topo

### 在虚拟机运行以下指令创建topo

```bash
sudo  mn 
```

此时，在虚拟机中含以下网络节点

```
hosts:  h1 h2 
switches: s1 
links: (h1, s1) (h2, s1) 
controller：c0 
```

其中h1和h2的ip分别为`10.0.0.1`和`10.0.0.2`
### 在宿主机中创建topo网络
新建topo-2sw-2host.py
```py
from mininet.topo import Topo

class MyTopo( Topo ):
    "Simple topology example."

    def build( self ):
        "Create custom topo."

        # Add hosts and switches
        h3 = self.addHost( 'h3',ip='10.0.0.3' )
        h4 = self.addHost( 'h4',ip='10.0.0.4' )
        leftSwitch = self.addSwitch( 's3' )
        # Add links
        self.addLink( h3, leftSwitch )
        self.addLink( leftSwitch,h4)
topos = { 'mytopo': ( lambda: MyTopo() ) }
```
通过命令`sudo mn --custom topo-2sw-2host.py --topo mytopo`创建网络topo
其中h1和h2的ip分别为`10.0.0.3`和`10.0.0.4`
## 关闭控制器
> 控制器能够帮助switch建立流表，如果要手动建立nodes链接关系，需要先关闭控制器。

*注意：也可以在mn命令的最后添加 `--controller remote`关闭controller，以省略以下步骤*
在关闭控制器前测试h1与h2之间互ping，因为controller的存在，彼此能够ping通。
在宿主机和虚拟机中分别输入`sudo killall controller`关闭控制器，这时候再尝试ping，发现无法ping通。因为switch中流表为空。
执行`sh ovs-ofctl dump-flows s1`,可以看到流表为空，其信息如下
```bash
mininet> sh ovs-ofctl dump-flows s1
NXST_FLOW reply (xid=0x4):
```
## 创建vxlan
运行` sh ovs-vsctl add-port s1 vxlan  `添加vxlan端口。
在虚拟机中，端口可以成功成功创建，但在宿主机中创建失败，提示错误信息：
```
mininet> sh ovs-vsctl add-port s13vxlan
ovs-vsctl: Error detected while setting up 'vxlan': could not open network device vxlan (No such device).  See ovs-vswitchd log for details.
ovs-vsctl: The default log directory is "/var/log/openvswitch".
```
解决方案如下
```
The port‘s name should be a exist interface use ifconfig to see, such as eth0. If you just want to use a virtual port name to make a test you should 
specify the port's type like ovs-vsctl add-port br0 port0 -- set Interface port0 type=internal or ovs-vsctl set Interface port0 type=internal
```
将指令改为
```
 sh ovs-vsctl add-port s3 vxlan   -- set Interface vxlan type=internal
```
在虚拟机中输入以下指令
```
sh ovs-vsctl set interface vxlan type=vxlan option:remote_ip=10.0.0.7 option:key=100 ofport_request=10
```
其中 ip地址是宿主机的ip，key是vxlan的标签，opport_request是端口名称
在宿主机中需要将以上命令的ip改为虚拟机的ip地址。
##  总结
以上建立的网络形式如下
![20190725110710.png](https://raw.githubusercontent.com/zdzh/pothos/master/img/20190725110710.png)
其中R为路由器，s1和s2为交换机，h1-h4为主机

### 同一交换机下的主机通信

![20190725113623.png](https://raw.githubusercontent.com/zdzh/pothos/master/img/20190725113623.png)

1. h1尝试ping h2时，拥有h2的ip地址但没有h2的mac地址。因此h1首先尝试通过arp获取h2  mac地址。
2. h1  发送 arp给 s1，s1收到arp后进行广播，同时记录h1的mac地址和端口的映射。h2收到广播后发现与自己的ip一致，根据广播给定的ip地址向s1发送响应，s1将响应发送给h1，同时s1记录h2的mac地址和端口的映射。
3. h1获取h2的mac地址后，在包里面加入h2的ip地址和mac地址并发送给s1.
4. s1收到包后，检查mac地址，找出对应的h2端口映射，将包发送到h2对应的端口
5. h2收到包后，匹配包的ip地址，ip地址一致则对包做进一步处理


