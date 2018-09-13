# list6
## 环境变量(environment variable)
- 全局变量，用`env`or`printenv`，指定查看变量用`printenv`，`$`引用变量作为值或者参数
- 局部变量和用户设定变量以及全局变量用`set`
- 设置变量
    - 局部变量：`variable_name=values`直接给变量名赋值，注意**不可以有空格**，然后可以`echo $variable_name`查看值
    - 全局变量：变量赋值后，`export variable_name`即可。父shell定义的全局变量被子shell修改后仅在本shell有效，不影响父shell
- 删除变量
`unset varible_name`即可
- $PATH 搜索路径变量
    - 不在该变量内的路径的命令无法直接使用。
    - 临时修改PATH
        - `PATH=$PATH:/absolutely_pathname`
        - `PATH=$PATH:.`当前目录加入PATH
- 定位系统环境变量
登入linux系统启动一个bash shell时，默认情况下bash会在*启动文件*又称*环境文件*中查找命令。查找的文件根据启动bash shell的方式。
1.登陆时作为默认登陆shell
2.非登陆shell的交互式shell
3.运行脚本的非交互shell

### 默认登陆shell
- 通过以下启动文件中读取命令
```java
/etc/profile
$HOME/.bash_profile
$HOME/.bashrc
$HOME/.bash_login
$HOME/.profile
```
- /etc/profile   --默认的主启动文件
内容迭代了`/etc/prifile.d`目录下的内容
- 剩下的启动文件的作用：提供一个用户专属的启动文件来定义该用户所用到的环境变量。按照以下顺序运行第一个被找到的文件，其余被忽略
$HOME/.bash_profile
$HOME/.bash_login
$HOME/.profile
其中$HOME/.bashrc是通过其他文件运行的
比如    $HOME/.bash_profile文件内就会查询bashrc

### 交互式shell
比如键入`bash`启动的为交互式shell
- 不会访问`/etc/profile`
- 只会检查`$HOME/.bashrc`
    - 作用：
    1.查看/etc目录下通用的bashrc文件
    2.为用户提供一个定制自己的命令别名(alias)和私有脚本函数

### 非交互式shell
系统执行shell脚本时用的就是这种shell
- 环境变量`BASH_ENV`，shell启动一个非交互式shell进程时，会检查该环境变量来查看要执行的启动文件。

- 环境变量持久化
    - 在/etc/profile.d目录中创建一个以.sh结尾的文件。把所有新的或修改过的全局环境变量设置放在这个文件中。
    - **most**存储个人永久性bash shell变量的地方是`$HOME/.bashrc`文件，适用于所有类型的shell进程。
        - **如果设置了`BASH_ENV`变量，除非这个变量指向`$HOME/.bashrc`，否则应该将*非交互式shell*的用户变量放在别的地方**

#### 环境变量数组
```
 variables = (one, two, three,  four)
 echo $variables  显示第一个
 echo ${variables[2]} 显示第三个
 echo ${variables[*]} 显示所有
 variables[2] = seven 更改第三个的值
 unset varibales[2] 删除第三个，但是索引还在
```

# list7
- umask root默认0022 normal默认0002
- 文件默认666， 目录默认777
## 共享文件
1.SUID: 当file被使用时，调用它的程序会以file属主权限运行
2.SGID: file-程序会以file属组的权限运行； Dir-目录中创建的新文件以目录的默认属组作为默认属组
3.粘着位：进程结束后文件还驻留(粘着)在内存中
```
mkdir directory
	#新建一个目录
chgrp shared directory
	#更改目录属组为shared
chmod g+s directory
	#组权限增加SGID位
umask 002
	#共享组内的用户更改掩码
cd directory
touch testfile
	#新建的文件就是shared
ll
```

# list8
- lvm逻辑卷，方便扩展物理磁盘

# list9
yum
- 查看
    - `yum list installed` 列出已安装包
    - `yum list special_soft` 列出特定软件包信息
    - `yum provides file_name`查找特定文件属于哪个软件包
- 安装
    - `yum install package_name` 网上安装
    - `yum localinstall package_name.rpm` 本地安装rpm软件包
- 更新
    - `yum list update` 更新列表
    - `yum update package_name` 更新特定包
    - `yum update` 全体更新
- 卸载
    - `yum remove package_name` 只删除软件包而保留配置文件和数据文件
    - `yum erase package_name` 全删
- 处理损坏的包依赖关系
    - 依赖关系被覆盖 `yum clean all`再`yum update`
    - 不行就`yum deplist package_name`显示所有包的库依赖关系以及什么嘛软件可以提供这些库依赖关系。
    - 不行就`yum update --skip-broken`胡列依赖关系损坏的哪个包，继续去更新其他软件包。
- yum软件仓库
    - `yum reolist`查看软件仓库

源码安装
1.解压
2.`./configure`
3.`make`
4.`make install`

# list 10
##vim
- 编辑数据
1. x 删除光标所在位置的字符
2. dw 删除光标所在位置的单词
3. d$ 删除光标所在位置到行尾的内容
4. J 删除当前光标所在行行尾的换行符
5. A 行尾追加
6. r char 用char替换当前光标位置的单个字符
7. R text 类似Del，直到ESC

- 查找和替换
1. :s/old/new/ 用new替换old(一次)
2. :s/old/new/g 替换一行中所有
3. :n,ms/old/new/g 替换行号n到m的所有old
4. :%s/old/new/g 替换所有
5. :%s/old/new/gc 替换所有，但是提示
