# RHEL7 的网络管理
- LInux下端口号的分配
    - TCP和UDP采用16位的端口号来识别应用程序 0~65535
    - TCP/IP的临时分配1024-5000之间的端口，大于5000的是为其他服务保留的
    - /etc/services 查看端口

- netstat 查看端口的监听状态
    - tcp端口：anpt udp端口：anpu 全部：anput
    - netstat -antup | grep : xx
    - 参数
        - -a , --all
        - -n , --numeric : don't resolve names
        - -p , --programs
        - -t , 显示tcp连接
        - -u , 显示upd连接

## 配置网络和IP地址
- 方法一：numtui- edit enoxxx
- 方法二：修改网卡配置文件 vim /etc/sysconfig/network-scripts/ifcfg-enoxxx

    	TYPE="Ethernet"
        BOOTPROTO="none"	#启动的协议: none不指定\| static静态 \| dhcp动态IP
        DEFROUTE="yes"
        IPV4_FAILURE_FATAL="no"
        IPV6INIT="yes"
        IPV6_AUTOCONF="yes"
        IPV6_DEFROUTE="yes"
        IPV6_FAILURE_FATAL="no"
        NAME="eno16777736"
        UUID="00256499-0760-4659-bc30-013168ad8252" #唯一标识
        DEVICE="eno16777736" 	#设备名称
        ONBOOT="yes"	#是否激活网卡
        IPADDR="192.168.1.10" # 配置的IP地址
        PREFIX="24"	# 掩码长度
        GATEWAY="192.168.1.1"	#配置网关
        DNS1="8.8.8.8"
        IPV6_PEERDNS="yes"
        IPV6_PEERROUTES="yes"
        IPV6_PRIVACY="no"
- 在RHEL7 中增强了NEtworkManager服务功能，弱化了network的功能
- systemctl status NetworkManager 确定服务开启，否则无法通过nmtui工具配置网络

- 修改主机名配置文件
    - /etc/hostname
    - 在之前可用`/etc/sysconfig/network`配置
- 配置hosts文件

    - /etc/hosts
- ping 命令格式
    - `-c 数目` 在发送指定数目的包后停止
    - `-i 秒数` 设定间隔几秒送一个网络封包给一个机器，预设值是一秒一次，秒数至少为200ms

# shell基本概述
- linux的shell是一种特殊的应用程序，可以通过/etc/shells文件查看
- /bin/bash 是大多数linux中默认的shell解释器
    ​    [akarin@akarin test]$ cat first.sh
    ​    #! /bin/bash
    ​    # this is my first shell-script
    ​    touch 1.txt
    ​    ifconfig
`#！ /bin/bash`是为了声明，以下所写的均为bash语言
```python
[akarin@akarin test]$ chmod +x first.sh #给权限
[akarin@akarin test]$ ./first.sh #执行
```
- 执行脚本的不同方式
    - 使用绝对路径
    - 使用相对路径，比如`./`
    - 使用sh命令 格式:`sh /路径/脚本名字` **无需执行权限**
    - 使用bash命令 格式:`bash /路径/脚本名字` **无需执行权限**
    - `ll 'which sh'`可知sh就是bash(这里的'应该为\`)
##- shell 的变量
- 常见的shell变量有自定义变量，环境变量，位置变量，预定义变量
- 一般用echo输出变量的值 `echo $变量名 [$变量名]`
- 变量名和后面的字符容易混淆的时候应该使用{}`echo ${变量名} other`
- read `read 变量1 变量2`
    - `read -p "display on the screen" 变量`
- 数值变量的运算
    - shell环境中只能进行比较简单的整数运算，整数的运算主要是用过内部命令expr进行运算
    - `变量1 运算符 变量2` **必须有空格**
    - `+` `-` `\*` `/` `%`
    - `value = $(expr $A \* $B)`

## 特殊shell变量
### 环境变量
- 环境变量 `env`查看
- 环境变量的配置文件在
    - `/etc/profile`(全局)
    - `/home/YOURUSERNAME/.bash_profile`(局部)

- `$PWD` ，pwd就是调用了这个变量才能进行输出
```python
        [akarin@akarin test]$ env | grep "PWD"
        PWD=/home/akarin/Desktop/test
        OLDPWD=/home/akarin/Desktop
        [akarin@akarin test]$ pwd
        /home/akarin/Desktop/test
        [akarin@akarin test]$
```
- $PATH 定义命令的默认搜索路径 **只有自己执行的命令在PATH变量包括的目录下，才可以直接使用并用tab不去，否则只能通过绝对路径or相对路径使用**
- $USER  用户名
- $HOME  家目录
- $SHELL  使用的shell
- 将缩写的脚本放在$PATH的默认搜索路径中
    - 临时 `PATH = '$PATH:/root'` 放在搜索路径后面
    - 永久
        `/etc/profile`(全局)
        `/home/YOURUSERNAME/.bash_profile`(局部)
    - 立即使用需要 `source 配置文件`加载一下

### 位置变量
- 当执行命令行操作死第一个字段表示命令字或程序名，其余的字符串参数按照从左到右的顺序一次给位置变量赋值
- 类似c语言的 *argv[0]
		`[akarin@akarin test]$ vim add.sh`
    ```python
   #! /bin/bash
   # add demo
   SUM=$(expr $1 + $2)
   echo "$1 + $2 = $SUM"
   [akarin@akarin test]$ chmod +x add.sh
   [akarin@akarin test]$ ./add.sh 10 20
   10 + 20 = 30
    ```

### 预定义变量
- $# 命令行中位置变量的个数(程序执行了几个位置参数)
- $* 所有位置变量的内容(具体的内容，比如/boot)
- $? 上一个命令执行后返回的状态，当返回状态值为0时表示执行正常，非0表示执行异常or出错，取值在1-127
- $0 当前执行的进程/程序名(就是当前执行的命令或程序的名字)
- $! 表示上一个命令的最后一个参数

# sed 和 awk
