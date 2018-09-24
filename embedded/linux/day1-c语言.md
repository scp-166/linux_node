# c语言

## Gcc

- 安装：

  配置yum源
  `sudo yum install -y centos-release-scl-rh centos-release-scl`
  以上是官方的源， 也可以用中科大的源。这样可以更快一点。
  `sudo yum install devtoolset-4-gcc  devtoolset-4-gcc-c++`

  | 数字 | gcc 版本号 |
  | :--: | :--------: |
  |  3   |   4.9.2    |
  |  4   |   5.3.1    |
  |  6   |   6.3.1    |
  |  7   |   7.2.1    |


  使其在当前shell生效

  ```c
  source /opt/rh/devtoolset-3/enable
  gcc -v
  ```


## 编译过程

- 编译`/opt/rh/devtoolset-3/root/usr/libexec/gcc/x86_64-redhat-linux/4.9.2/cc1-o /tmp/a.s ` 就是 `gcc -S`
- 汇编 `as -o a.o a.s` 就是 `gcc -c`
- 链接 ` /opt/rh/devtoolset-3/root/usr/libexec/gcc/x86_64-redhat-linux/4.9.2/collect2 -o build a.o+...`就是 `gcc -o`
- 预处理 `gcc -E a.i xxx.c`文本替换



## gcc选项

- `-I 指定查找头文件路径`



## 宏

### 预定义宏

`__FUNCTION__` 当前函数名

`__LINE__`	当前行号

`__FILE__` 当前文件名

**可以直接使用**



### 条件编译宏

```c
#include <stdio.h>

int main()
{
#ifdef ABC
        printf("all ready defined\n");
#endif
        printf("hello\n");
        return 0;
}
```

**gcc -D ABC  或者 gcc -DABC** 等同于 `#define ABC`



### 宏展开

`#` 字符串化

`##` 连接符号

```c
#define ABC() #x
#define ABC(x) day##x
```

example:

```c
#include <stdio.h>
#define add(x) #x
#define day(x) day##x

int main()
{
        int day1=10;
        int day2=20;
        printf("%s", add(a+b\n));
        printf("%d\n", day(1));
        return 0;
}

```

output:

```c
a+b
10
```



## 关键字和运算符操作

### 数据类型

- 编译器最优的处理大小：系统一个周期，所能接受的最大处理单位

- 符号

  - unsigned 数据
  - signed 数字

- 整型

  - 300l long型

- 浮点数

  - 1.1 double型
  - 1.1f float型

- enum

  ```c
  // enum是一个对整型数据的集合的整合，sizeof只有4
  #include <stdio.h>
  enum name{MON=10, TUE=100, WED}; // name如果不用可以不写，常量列表默认为0
  
  int main()
  {
      printf("%d\n", MON);
      printf("%d\n", TUE);
      printf("%d\n", WED);
      return 0;
  }
  
  //output: 10 100 101
  ```



### 类型修饰符

1. auto 默认修饰符
2. register 不可以取地址
3. static  函数内部：公用 函数外部：代码本地化 函数：函数本地化
4. const
5. extern
6. volatile : 优化选项



### 运算符

1. `<< `：右加0
2. `>>`： 左加符号位

**重要**

```c
//清除第n位
a & ~(0x1 << n)
//设置第n位为高电平
a | (0x1 << n)
```



## c语言内存空间的使用

### 指针

1. 在*32*bit系统中，指针需要*4*个字节

### 指针和修饰符

- const

  const char *p; ---> 类似指向一个字符串

  char * const p; ----> 类似指向一个硬件资源

  const char * const p; ----> 类似指向rom

- volatile

  防止优化指向内存地址(注意硬件)



```c
#include <stdio.h>
int main()
{
    int a = 0x12345678;
    int b = 0x99991199;
    
    int *p1 = &b;
    char *p2 = (char *)&b;
    
    printf("%x %x %x\n", *(p1+1), p[1], *p+1);
    printf("%x %x %x\n", p2[1]);
    return 0;
}

//output
/*
12345678 12345678 9999119a
11
*/
```

**变量是地址递减添加**



### 数组

```c
char buf[10] = {"abc"};
char buf[10] = "abc"; //开辟俩空间，一个是buf数组，一个是"abc"，这个初始化是将"abc"拷贝给buf数组
buf[2] = 'k'; //right
char *p = "abc";
p[2] = 'k'; //wrong
```

strcpy： 容易造成内存溢出

strncpy：遇见`\0`就结束，在数据拷贝时不太适合

memcpy(void *des, const char *str, size_t n): 数据拷贝



char ch; //字符空间

unsigned  char ch; //非字符空间，看成data



```c
char b[3][4];
char **p = b; //wrong, b is char (*)[4]
```



**二维数组和二维指针毫无关系** 

- 指针数组 `char *p[5]`:一个大小为5个单位的数组，各个内容是char型的变量地址
- 数组指针 `char (*p)[5]`:一个指向五个char型变量的指针



## 内存分布

|                内核空间                |              应用程序不许访问               |
| :------------------------------------: | :-----------------------------------------: |
|                 栈空间                 |                  局部变量                   |
|             运行时的堆空间             |                   malloc                    |
| 全局的数据空间 \| 只读数据段 \| 代码段 | (初始化、未初始化) \|  "hello word" \| code |

