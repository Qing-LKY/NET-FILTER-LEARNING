# NET-FILTER LEARNING

参考我的另一个项目 [Lab-Linux-Kernel-Module-Device](https://github.com/Qing-LKY/Lab-Linux-Kernel-Module-Device)。

## 实验目的

了解 NetFilter 框架，掌握 Linux 内核模块编程的方法，熟悉 Netfilter 框架进行数据拦截的方法，能够利用 Netfilter 框架实现网络数据包的控制。

## 实验要求

阅读课本 16-17 章；掌握Linux内核模块的编程方法；掌握Netfilter框架钩子函数设计与实现方法。

能够利用Netfilter框架和钩子函数实现以下功能：

1. 禁止 ping 发送；
2. 禁止某个 IP 数据包的接收；
3. 禁止某个端口的数据响应。
