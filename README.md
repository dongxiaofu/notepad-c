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

删除指定行数据
显示指定行数据
显示全部数据
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
    
