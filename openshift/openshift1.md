# openshift一：什么是openshift

Openshift是一个开源的容器云平台，底层基于当前容器的事实标准编排系统[Kubernetes](#%E4%BB%80%E4%B9%88%E6%98%AFKubernetes)和docker引擎，企业可以基于此平台搭建内部PAAS平台，贯穿CI/CD流程，提高企业IT效率，拥抱DevOps和敏捷开发。
<!---more--->

## 什么是Paas

PaaS（Platform as a Service，平台即服务）最早是在云计算领域被提出。如下图所示，将企业IT服务分为九层，传统自建数据中心九层设施都需要企业自己维护，成本极高。而云计算架构就相当于吧九层架构中的底层一部分外包给云计算服务提供商，根据外包的层次不同，分为IaaS(Infrastructure as a Service，基础设施即服务)，PaaS，SaaS（Software as a Service）三层。

- IaaS 层为基础设施运维人员服务、提供计算、存储、网络以及其他硬件资源，云平台使用者可以在上面部署和运行包括操作系统和应用程序在内的任意软件，无需再为基础设施的管理而分心。
- PaaS 层为应用开发人员服务，提供支撑应用运行所需的软件运行时环境，相关的工具与服务，如数据库服务、日志服务、监控服务等，让应用开发者可以专注于交付业务价值的代码而无需关心应用所需脚手架。
- SaaS 层为一般用户（最终用户）服务，提供了一套完整可用的软件系统，让一般用户无需关心技术细节，只需通过浏览器、应用客户端的方式就能使用部署在云上的应用服务。SaaS 产品比如客户关系管理系统、邮件、虚拟桌面、通信、游戏等。


## 什么是Kubernetes

Kubernetes是一个开源容器编排引擎，用于自动化容器化应用程序的部署，扩展和管理。 Kubernetes的基本概念包括： 
- 一个或多个工作节点（worker node）负责工作负载
- 一个或多个管理节点（master node）负责管理工作负载
- 将容器封装在名为Pod的部署单元，使用Pod为容器提供额外的元数据并且提供在单个部署实体中对多个容器进行分组的功能
- 创建特殊的资源。例如，服务表示一组Pod和访问策略，该访问策略允许容器没有特定的ip地址也能连接服务。复制控制器（Replication controllers）是另一种用于控制同一时间的Pod副本数量的特殊资源，可以使用此功能自动扩展应用程序以适应其当前需求。

## 什么是OKD

OKD是Kubernetes的发行版，也是openshift的社区版，针对持续应用程序开发和多租户部署进行了优化。OKD在Kubernetes之上添加了开发人员和运营工具，以便为小型和大型团队实现快速的应用程序开发，轻松部署和扩展以及长期生命周期维护。
OKD是嵌入了Red Hat OpenShift中的上游Kubernetes发行版，并通过安全性和其他集成概念进行扩展。 OKD在github和文档中也称为Origin。

## openshift层次结构

OpenShift v3是一个分层系统，旨在尽可能准确地公开底层Docker格式的容器镜像和Kubernetes概念，重点是帮助开发人员轻松组合应用程序。例如，安装Ruby，推送代码和添加MySQL。
其中，docker提供了打包和创建基于linux的轻量容器镜像的抽象；Kubernetes提供了集群管理以及在多台主机上编排容器的功能。OKD提供了以下功能 ：
- 帮助开发人员管理、构建和部署源代码
- 管理和推广大规模的流进系统的镜像
- 大规模的应用管理
- 组织大型开发人员组织的团队和用户跟踪
- 支持群集的网络基础结构

Openshift 实际上由三部分组成，核心部分实现容器的调度是封装的 Kubernetes， 除此之外还有一个内置的镜像仓库（Image Registry），这个仓库是可选的，Openshift 也可以配置使用 Dockerhub 或者企业自己的镜像仓库，最外层部分是一个友好的 Web 界面，用于展示和操作 Openshift 的资源。   
如下图所示，Openshift 要成为一个完整的数字化平台需要依赖于两个外部系统，一个代码库，一个是持续集成服务，事实上这两个外部服务也是可以跑在 Openshift 里面的。右边的灰色矩形就是 Openshift 的主要架构了，它的上层是一个路由（Router），用于 DNS 解析和转发，确保用户能够调用到 Openshift 集群中的服务。中间部分是跑在 RHEL 操作系统上的 Kubernetes 集群，侧面是外部存储服务，因为集群里的计算单元是漂浮的，所以通常 Kubernetes 集群只提供计算能力，数据持久外需要依赖外部的比如说 S3，EBS 等云服务商提供的存储服务。最下层同样也是由云服务商提供的基础设施服务。

![](https://raw.githubusercontent.com/zdzh/photo/master/img1/20190812112313.png)



## 参考资料

官网链接:https://www.openshift.com/  
官方链接：https://access.redhat.com/documentation/en-us/openshift_container_platform/4.1/html/architecture/architecture
https://www.duyidong.com/2017/06/14/kubernetes-and-openshift/