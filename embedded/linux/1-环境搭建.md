# day1

## zmodem

centos7 运行 `sudo yum install lrzsz`安装zmodem服务

rz :receive base on zmodem 接收文件

sz source: send base on zmodem 发送文件



## samba服务

- 永久关闭selinux

  ```python
  vim /etc/selinux/config #将SELINU置为disabled
  ```

- 关闭防火墙开机启动

  ```c
  systemctl stop firewalld
  systemctl disable firewalld
  ```

- 安装`sudo yum install samba `

- 配置 `vim /etc/samba`

  ```python
  [akarin_share] #新建
          comment = akarin share  #名字
          path = /home/akarin/local #目录
          writable = yes	#可写
          browseable = yes	#可读
  
  ```

- 配置samba用户权限 `smbpasswd -a esist_user_name`  **esist_user_name是linux已有用户**

  samba可以共享linux的用户名而不共享密码，所以添加密码以防使用相同密码

- windows下`ctrl+r`运行`\\虚拟机ip地址`进入samba共享目录，输入账号和密码（上文的esist_user_name和密码）

- 如果可以，则在windows下添加 *映射网络驱动器*， 文件夹设置为`\\虚拟机ip\akarin_share`即可



## source insight

- 新建工程的时候，源文件路径和工程路径最好不要在一起
- 工程新建好后，符号链接有问题可以在*project windows*窗口（可在view->Panel下找到）右键`synchronize file`进行符号链接