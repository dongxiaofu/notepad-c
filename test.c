#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insertMenu();

int main() {
    char *c;
    int count = 0;

    while (1){
        printf("time:%ld\n", time(NULL));
        if(count == 2){
            printf("count : %d\n", count);
            break;
        }
        count++;
    }

    // todo 功能粗糙
//    insertMenu();


    return 0;
}
int insertMenu() {
    int c;
    while(1){
        time_t time1 = time(NULL);
        printf("%s===%ld\n", "while0", time1);
        while (1) {
            printf("\n\t1.插入一行文字\n");
            printf("\t2.插入一段文字\n");
            printf("\t3.返回上级菜单\n");
            printf("\t请按数字选择：\n");
            scanf("%d", &c);
            printf("c = %d\n", c);
            if (1 <= c && c <= 3) {
                printf("break\n");
                break;
            }
        }
    }

    return c;
}
