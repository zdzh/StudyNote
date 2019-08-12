# 虚拟网络



## Net namespace

在 Linux 中，网络名字空间可以被认为是隔离的拥有单独网络栈（网卡、路由转发表、iptables）的环境。网络名字空间经常用来隔离网络设备和服务，只有拥有同样网络名字空间的设备，才能看到彼此。 可以用ip netns list命令来查看已经存在的名字空间。

## iptables

*iptables* 是一个配置 Linux 内核 [防火墙](https://wiki.archlinux.org/index.php/Firewall) 的命令行工具，是 [netfilter](https://en.wikipedia.org/wiki/Netfilter) 项目的一部分。术语 *iptables* 也经常代指该内核级防火墙。iptables 可以直接配置，也可以通过许多 [前端](https://wiki.archlinux.org/index.php/Firewalls#iptables_front-ends)和[图形界面](https://wiki.archlinux.org/index.php/Firewall#iptables_GUIs)配置。iptables 用于 [ipv4](https://en.wikipedia.org/wiki/Ipv4)，*ip6tables* 用于 [ipv6](https://en.wikipedia.org/wiki/Ipv6)。

