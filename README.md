## 20200314
### 菜单
1.从一级菜单进入二级菜单
2.从二级菜单返回一级菜单


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