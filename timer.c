//定时器
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(int num, char *arg[]) {
    //arg数组存放指针
    //printf("个数：%d 参数值1：%s 参数值2：%s 参数值：%s\n",num,arg[0],arg[1],arg[2]);
    if (num != 2) {
        printf("必须输入一个数字:%s\n", arg[0]);
        exit(1);
    }
    int duration = atoi(arg[1]);
    if (duration <= 0) exit(1);
    //设置启动时间
    time_t start, current;
    time(&start);
    printf("开始时间:%s \n", ctime(&start));
//    do {
//        //设置当前时间
//        time(&current);
//        printf("current time:%s\n", ctime(&current));
//    } while ((current - start) % duration != 0);

    while (1) {
        time(&current);
        if ((current - start) % duration == 0) {
            sleep(2);
            printf("current time:%s\n", ctime(&current));
        }
    }


    printf("当前时间:%s \n", ctime(&current));

    return 0;
}
