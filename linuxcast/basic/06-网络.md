#网络
## 子网掩码
- ipv4地址的32bit分为网络部分和主机部分
- 子网掩码确定网络部分的位数
- 192.168.1.10/24 表示前24(192.168.1)位是网络地址
## 基本网络参数
- 配置一个局域网通信的计算机
    - ip地址
    - 子网掩码
- 配置一个跨网段通信的计算机
    - ip地址
    - 子网掩码
    - 网关
- 配置一个可上网的计算机
    - ip地址
    - 子网掩码
    - 网关
    - DNS
# 网络基本配置
## 以太网连接
- 以太网接口为：eth0，eth1
- 通过`lspci`/`isusb`查看网卡硬件信息
- 命令ifconfig
    - `ifconfig -a`查看所有接口
    - `ifconfig eth0`查看特定接口
- ifup，ifdown用来启用、禁用一个接口
    - `ifup eth0`
    - `ifdown eth0`

## 配置网络信息
- `setup`配置网络信息
- 结束后使用`ifup`启动网卡

## 网络相关配置文件
- 网卡配置文件
`/etc/sysconfig/network-scripts/ifcfg-ethxxx`
- DNS配置文件
`/etc/resolv.conf`
- 主机名配置文件
`/etc/sysconfig/network`
- 静态主机名配置文件
`/etc/hosts`

## 网络测试命令
- 测试网络连通性 `ping`
- 测试DNS解析 `host` and `dig`
- 显示路由表 `ip route`
- 追踪到达目标地址的网络路径 `taceroute`
- 使用mtr进行网络之路测试（结合了traceroute和ping） `mtr`

## 修改主机名
- 实时修改主机名 `hostname theNameYouWant`
- 永久性修改主机名 
    - 在`/etc/sysconfig/network`
    - 修改`HOSTNAME=theNameYouWant`

## 故障排查
- 先查看网络配置信息是否正确：ip、子网掩码、网关、DNS
- 查看到达网关是否连通 `ping 网关ip地址`
- 查看DNS解析是否正确 `host`