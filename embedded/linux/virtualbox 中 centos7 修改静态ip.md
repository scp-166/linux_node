# virtualbox 中 centos7 修改静态ip

1. 关闭虚拟机后，在virtualbox的设置中选择网络

2. 设置网络1为 *仅主机网络*

3. 设置网络2为 *nat*

4. virtualbox主窗口`ctrl+w`查看网卡ip地址(基本上都是192.168.56.1)

5. 启动虚拟机

6. 编辑 /etc/sysconfig/network-scripts/ifcfg-enp0s3

7. 修改如下

   ```c
   TYPE="Ethernet"
   PROXY_METHOD="none"
   BROWSER_ONLY="no"
   BOOTPROTO="static"  //修改这里
   DEFROUTE="yes"
   IPV4_FAILURE_FATAL="no"
   IPV6INIT="yes"
   IPV6_AUTOCONF="yes"
   IPV6_DEFROUTE="yes"
   IPV6_FAILURE_FATAL="no"
   IPV6_ADDR_GEN_MODE="stable-privacy"
   NAME="enp0s3"
   UUID="c4211b33-1501-4c26-bac8-eca1beb3ece9"
   DEVICE="enp0s3"
   ONBOOT="yes"
   IPADDR="192.168.56.100"	//添加这里，56为网关
   ```

8.  `reboot`后看下主机能否ping通虚拟机

9. 如果没有配置两个网卡，仅主机模式是无法上网的