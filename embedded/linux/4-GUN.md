# GUN

## gcc

### 编译过程参数



|     参数      |             解释             |
| :-----------: | :--------------------------: |
|      -c       | 只编译不链接，生成目标文件.o |
|      -S       |  只编译不汇编，生成汇编代码  |
|      -E       |           只预编译           |
|      -g       |         包含调试信息         |
|    -o file    |       指定目标输出文件       |
| -I(字母I) dir |        搜索头文件路径        |



### 库选项

- 静态链接库

  - 编译

  ```shell
  #先生成目标文件.o
  gcc -c [-o test] test.c
  
  ar crv [*.a] [*.o] #.a是目标静态链接库
  ```

  - 运行

    ```shell
    gcc -o [file] [file.c] [file.a]
    ```

- 动态链接库

  - 编译

    ```shell
    #生成位置无关的目标代码
    gcc -fPIC -c [*.c]
    
    gcc -shared -o [*.so] [*.o]
    ```

  - 调用

    ```shell
    gcc -o [file] [file.c] -L./ [file.so] #注意./ 和 file.so之间有空格
    ```

  - 运行可执行文件(关于动态链接库的系统路径PATH)
    1. 将.so放在/usr/lib下
    2. /etc/下的ld.so.conf包含ld.so.conf.d/*.conf,其下有libc.conf文件，保存自定义的lib设置

  - 错误`error while loading shared libraries: libtest.so: cannot open shared object file: No such file or directory`

  - 见博文[solution](https://www.cnblogs.com/wangluochong/p/4108131.html)



### 警告选项



|   选项    |            解释             |
| :-------: | :-------------------------: |
|    -w     |        关闭所有警告         |
|   -Wall   | 发出gcc提供的所有有用的警告 |
| -pedantic |    发出ansii c的所有警告    |





### 优化选项



|  选项   |                       解释                        |
| :-----: | :-----------------------------------------------: |
| -Olevel | 优化等级，一般只是最终发布的时候才用(level是等级) |

