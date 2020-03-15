#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main() {
    char *str = "how are you?\n";
    printf("str[0]:%c\n", str[0]);      // OK
    char str2[strlen(str) - 1];
    int i = 0;
    while (*str != '\n') {
        str2[i] = str[i];       // Segmentation fault: 11，上面str[0]可以，这里为啥不行？
        i++;
    }
    str2[i] = '\0';
    printf("str2:%s######len:%ld\n", str2, strlen(str2));
    char *str3 = "A";
    printf("str3:%s######len:%ld\n", str3, strlen(str3));

    return 0;
}
