#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int flag = 1;//全局标志位
void *fun(void *p) {
    int i = 0;
    for (i; i < 10; i++) {
        printf("fun i=%d\n", i);
    }
    printf("fun bye bye\n");
    flag = 0;
    return NULL;
}

int main() {
    pthread_t th;
    if (pthread_create(&th, NULL, fun, NULL) < 0) {//pthread_create()函数参数请百度
        perror("pthread_create");
        return -1;
    }
//    sleep(1);//这次不用sleep函数，看是否main在用光了时间片后会交出时间片让其他等待程序执行呢
    int i = 0;
    while (flag) {
        printf("main i=%d\n", i++);
    }
    printf("main bye bye\n");
    return 0;
}