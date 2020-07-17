## 20200314
### 菜单
1.从一级菜单进入二级菜单
2.从二级菜单返回一级菜单
#### 功能
##### 已完成功能
1.在开头插入数据
2.追加数据
3.指定行、指定列插入数据
    在内存中操作；若直接操作文件，移动文件指针，不会，太麻烦。
4.在指定行插入一行数据
5.在指定行插入空白行
    调试，耗费时间非常多
    读取文件中的空白行，耗费时间非常多
6.删除指定行数据
7.显示指定行数据
8.显示全部数据
9.查找字符串返回第一个结果
10.查找字符串返回所有结果
11.字符串替换（一个）
12.打开文件
    遇到问题，未解决，在error-08分支;f。
    输出已经存在的文件，才能正确运行，否则出错。
==============================================================
上述功能，耗时四天，平均每天十个小时。内存中的数据链表结点异常；野指针；
不同操作的文件句柄互相污染。
一些功能，比如，删除某个字符串、删除多行，与已实现功能很相似，有时间再做。
优先级高的功能
==============================================================
13.所有文件操作在内存中进行，选择"存盘"菜单才保存到文件中。
14.自动保存，另外用一个线程每间隔几分钟就存储数据到文件中。
    多线程，调试，低效。查了资料，却没仔细去看。
15.统计中文字数。
    一个中文由三个负整数表示。统计字符串中所有负数编码的个数，然后除以3，结果是中文字数。
16.文件另存为
17.十六进制查看文件--查看英文文本文件
##### 未完成功能
18.其他功能，看我自己需要什么功能，或者模仿其他编辑器。
19.设置文档密码
    将密码存在到单独文件中，用二进制存储。
    文档的标识，用md5这种类型函数提取指纹，指纹+密码，一起存储。
    在保存文件的时候，更新指纹。
    打开文件时，检查是否存在指纹+密码锁，若存在，要求输入密码。
20.十六进制查看文件--查看中英混合文件
21.十六进制查看文件--查看可a.img，dd 生成的软盘镜像十六进制查看文件--查看jpg图片文件
##### 下级菜单与操作联系
1.所有菜单（不同级别）使用一套编码，编码非常大。

2.不同级别菜单使用独立的编码，不同级别菜单编码可以重复。

不知道怎么实现。

操作代码嵌入非一级菜单。

目前，我把菜单选择代码和操作代码分开。

方法：将操作代码嵌入菜单中。

3.在文件开头插入数据
>1.用新数据新建文件，再把旧数据追加到文件。
>
>
>我的实现方法，执行一个操作之后，立即存盘；高效的做法，在内存中
>完成操作，最后存盘。
>
4.键盘交互式问题

在编辑器执行过程中，选择菜单，读取数据，都需要从键盘接收数据。

使用的是scanf，可是，scanf、fgets等这些输入函数之间互相影响。

如何接收含有空格的一行数据？

在fgets前面增加一个scanf来阻塞，等待键盘输入；
还是有点问题，数据丢失。


### 问题
#### scanf覆盖了链表的最后结点的数据
1.使用scanf后，一个全局链表的最后结点被修改成了scanf接收
到的数据。为什么会这样？

错误场景：文件 main.c 的 firstMenu，分支：error-01

解决：char *c = (char *)malloc(sizeof(char) * 100);

接收输入数据的变量，手动分配内存。改正场景：

分支：fix-01

#### 第二次读取有数据文件结果为空
2.写入文件，将函数终止代码由exit(0)改成return;后，文件
被清空。

场景重现：./main，选择3，输入行号1

文件 main.c 的 deleteLine，分支：error-02

解决：

loadAll第二次执行，读取数据为空，是因为第一次执行deleteLine
中的save没有关闭fp；第二次读文件时，在此fp基础上读文件。

关闭save中的fp，问题被解决。

分支：fix-02

#### while break后继续执行一次

    int insertMenu() {
        int c;
        while (1) {
            printf("\n\t1.插入一行文字\n");
            printf("\t2.插入一段文字\n");
            printf("\t3.返回上级菜单\n");
            printf("\t请按数字选择：\n");
            scanf("%d", &c);
            printf("c = %d\n", c);
            if (1 <= c && c <= 3) {
                printf("break\n");
                return c;
            }
        }
        return c;
    }
    
第一次等待输入，输入1后，执行到了if(1 <= c && c <=3)中，
但没有终止while，继续执行到了那些printf。

这是为什么？应该第一次输入1后，while就终止。

错误场景：

文件 main.c 的 insertMenu，分支：error-03

悬而未决

#### pointer being freed was not allocated

错误信息：

main(86572,0x10eef4dc0) malloc: *** error for object 0x10cf9ffac: pointer being freed was not allocated
main(86572,0x10eef4dc0) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6

文件：main.c  insertInLineNum函数 分支：error-04

#### 野指针

文件：main.c  insertInLineNum函数 第530行 ``free(str2);`` 分支：error-05

main(89173,0x110e8ddc0) malloc: *** error for object 0x7fcaec7001b7: pointer being freed was not allocated
main(89173,0x110e8ddc0) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6

去掉 ``free(str2)`` 后错误消失。

更正确的fix方法，未知。

#### 链表死循环

场景：main.c insertOneLine，输入 25,1,how are you 时，info->next是它自身 分支：error-06

    struct line *info;
    info = start;
    while (info){
        printf("info->num:%d###info->text:%s\n", info->num, info->text);
        info = info->next;
    }
    
偶发，原因未知。

怀疑，是野指针。将上面代码中的info改为info2后，多次测试未复现bug。

#### 文件链表结点顺序异常

场景：main.c loadFile 分支：error-07

顺序异常，原因未知。

把

    if (start == NULL) {
        start = info;
    }

改成

    if (tmp->num == 1) {
        start = tmp;
    }
    
 问题被修复。关键在于 `tmp->num == 1` 。
 
 修复分支 fix-07
    
#### Undefined symbols for architecture x86_64

错误信息：

Undefined symbols for architecture x86_64:
  "_createFile", referenced from:
      _main in main-3321f0.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)

在文件 main.c 中的 char *openFile()，分支 error-08


warning: GCC does not allow variable declarations in for loop initializers before C99

### 参考资料

用C开发查看HEX字节码的工具

https://blog.csdn.net/shaoyubin999/article/details/82950806

用C语言开发查看HEX字节码的工具--看程序如何进化

https://blog.csdn.net/shaoyubin999/article/details/82958273

你好，用 printf("%2x ", ch) 输出数据为：

00000000: ffffffe4  ffffffbd  ffffffa0  ffffffe5  ffffffa5  ffffffbd   a                                      .......

怎么才能只输出 e4 bd a0 e5 等呢？即，去掉前面的四个f。


