#include <stdio.h>
#include <stdlib.h>

int main() {
    char str1[30], str2[30]; //定义两个字符数组
    printf("scanf Enter:\n");
    scanf("%s", str1);
    printf("scanf : %s\n", str1);
    scanf("%s", str2);
    printf("scanf2 : %s\n", str2);
    char c;
    while((c=getchar()) != '\n'){
        putchar(c);
    }
    return 0;
}
