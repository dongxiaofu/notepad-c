#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
// 一个空白行是两个10，两个连续空白行是3个10，三个连续空白行是4个10
// \n 就是 10
int main() {
    char *filename = "/Users/cg/data/code/wheel/c/notepad/t";
    FILE *fp = fopen(filename, "r");
//    printf("char : %c\n", fgetc(fp));
//    return 0;
    int i = 0;
    char c;

    while ((c = fgetc(fp)) != EOF) {
        int i = 0;
        char str[20];
        if(c == '\n'){
            str[i] = c;
            continue;
        }
        str[i] = c;
        i++;
//        if(c == '\n'){
//            printf("n:%c",c);
//            printf("nd:%d\n",c);
//        }
//        continue;
        while ((c = fgetc(fp)) != '\n' && c != EOF){
            str[i] = c;
            printf("%d:c:%d\n", i, c);
            i++;
//            if(i == 25){
//                break;s
//            }
        }
        str[i] = '\n';
        printf("str = %s########", str);
    }
//    printf("lastc = %d\n", c);
    return 0;
    while (1) {
        if (i == 8) {
            break;
        }
        printf("%d##", fgetc(fp));
        i++;
    }

    return 0;
}
