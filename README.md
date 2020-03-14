## 20200314
### 菜单
1.从一级菜单进入二级菜单
2.从二级菜单返回一级菜单
#### 功能
##### 下级菜单与操作联系
1.所有菜单（不同级别）使用一套编码，编码非常大。

2.不同级别菜单使用独立的编码，不同级别菜单编码可以重复。

不知道怎么实现。

操作代码嵌入非一级菜单。

目前，我把菜单选择代码和操作代码分开。


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