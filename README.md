# LanguagePlus - 基于C语言描述的语言解释器

该语言解释器可以实现简单一些简单的语句功能，例如

- 变量的声明及赋值

- 变量与整形之间的加法运算

- 输出任意形式的加法表达式结果

- *输入Example*

![Image_Example](https://github.com/Marisa9961/LanguagePlus/blob/master/Document/Image/Image_Example.png)

- *输出各步执行的结果*

![Image_Result](https://github.com/Marisa9961/LanguagePlus/blob/master/Document/Image/Image_Result.png)

## 使用说明

### 基本语法

- 变量的定义必须要以`大小写字母`或`下划线`为起始，否则程序会进行报错

- 赋值类型仅允许**整形变量**

- 任何非法字符都会被词法解析器截断并报错

- 对于任意变量`x`的定义方式：

        x = value
        x = value1 + value2 + ...

- 对于任意变量`x`的输出方式：

        echo x
        echo x + value1 + value2 + ...

- 注意：程序并不强制以**空格**或**回车**作为换行：

        a = 1 + 2 
                    + 3
        echo a
        //输出结果仍为6

- 注意：**缺失语句成分**也将会由语法解析器进行报错

        = 1
        //Error:Missing an identifier after assign operator