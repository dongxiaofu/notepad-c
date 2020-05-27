#include <stdio.h>
#include <string.h>

int main(void) {
    int count;
    char *c = "我。t";
    for (int i = 0; i < strlen(c); i++) {
        printf("%d\n", c[i]);
    }

    return 0;
}