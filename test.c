#include <stdio.h>
#include <stdlib.h>

int insertMenu(int c);

int main() {
    char *c;
    int count = 0;
    // todo 功能粗糙
    int no;
    while (1) {
        printf("\n\t\t1.显示\n");
        printf("\t\t2.插入\n");
        printf("\t\t3.删除\n");
        printf("\t\t4.保存\n");
        printf("\t\t5.退出\n");
        printf("\t\t6.显示全部\n");
        printf("\t\t7.打开\n");
        printf("\t\t请选择一项功能：\n");
        scanf("%s", c);
        no = atoi(c);
        if ((1 <= no && no <= 9)) {
            if (no == 2) {
                // 进入插入菜单
                int res = insertMenu(no);
                // 3 是返回上级菜单
                if (res == 3) {
                    continue;
                }
            }
            break;
        }
    }


    return 0;
}

int insertMenu(int c) {
    printf("\n\t1.插入一行文字\n");
    printf("\t2.插入一段文字\n");
    printf("\t3.返回上级菜单\n");
    do {
        printf("\t请按数字选择：\n");
        scanf("%d", &c);
    } while (!(1 <= c && c <= 3));
    return c;
}
