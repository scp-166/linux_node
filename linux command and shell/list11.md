# list11
- 运行shell脚本
1. 将shell脚本文件所处的目录添加到PATH环境变量中；
2. 在提示符中用绝对或相对文件路径来引用shell脚本文件

### 命令替换
- 使用 反引号括起来
- 使用 $()

- 注意。命令替换会创建一个由运行脚本的shell创建出来的子shell来运行对应的命令。所以会无法使用脚本中所创建的变量

### 重定向输入和输出
- `>`
- `>>`
- `<`
- `<<` 内联输入重定向，需要指定一个文件标记作为划分输入数据的开始和结尾。注意作为开始和结尾的文本标记必须一致
		 wc << maker
         > test string 1
         > test string 2
         > maker
          2  6 28


### 数学运算
~~推荐用 variable = $[operation]
缺点是不能用浮点数~~
-bc
	-`-q` 去除欢迎界面
    使用`bc << maker options maker`来使用bc

### 退出码
退出码范围为0~255
`echo $?` 查看退出码，正常为0
- 脚本退出码
    - `exit value`value可以是变量
    - 结束后使用`echo $?`查看退出码mod256后的值

# list12
- if 判断命令退出码：为0进行then
		#单一if
		if command
        then
        	commands
        fi
        
        #嵌套if
        if command
        then
        	commands
        elif command
        then
        	commands
        elif command
        then
        	commands
        else # 这个属于最后一个elif
        	commands
        fi

- 然而if只能判断命令的退出码，对其他进行判断需要test
`test command`来替换if中`command`
test会对command测试，成功返回0
可以用`[ command ]`替换，注意空格
可以进行三类判断：
1. 数值比较 -不能用浮点数
2. 字符串比较 >和<需要/转义,否则会重定向
3. 文件比较
