#  mininet安装配置
## 安装mininet
## mininet使用
### 在VM中运行mininet
1. 安装VMware，在VMware中打开下载好的mininet虚拟机映像
2. 启动虚拟机，虚拟机的初始账号密码均为`mininet`
3. 输入`ifconfig -a`查看网卡信息，需要的网卡有eth0和eth1，其中一个为NAT，一个为host-only，若缺少网卡，则需要添加相应的网卡，添加方式如下
    - 在打开虚拟机对应的设置，为虚拟机添加网络适配器。
    - 重启虚拟机后，可以看见相应网卡已经添加进去但还未分配ip
    - 输入` sudo dhclient ethX`为ehtX自动分配IP地址
    - 在/ etc / network / interfaces中添加以下语句，之后会自动运行dhclient
        ```
          auto eth1 
            iface eth1 inet dhcp
        ```
4. 通过SSH在主机访问VM    
    在主机中输入`SSH -X [usr]@[address]`，此时会跳出警告，直接输入yes，之后输入VM账户密码即可连接到VM。其中usr是VM账户名，address是VM的ip地址。最后输入`xterm`打开控制vm的命令行窗口
##常用命令
```bash
$ sudo mn     # 打开mininet，启动默认网络拓扑
> help    # 帮助
> <node>  ping <node>  # 节点之间ping测试
> ping all # 所有节点之间ping测试
> py h1.setIP("10.0.0.1")       # 修改h1的ip地址
```
