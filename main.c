#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define DEBUG 0
#define FILE_IS_EMPTY "文件为空，请先增加内容"

const int MAX_LEN = 100;
char *test = "abc";

struct line {
    char text[MAX_LEN];
    int num;    // 行号
    struct line *prior;  // 上一行
    struct line *next;   // 下一行
};

struct line *start, *last;
int lineNum;
int targetLineNum;
char *filename;

// 载入文件
void loadFile(char *filename);

// 一级菜单
int firstMenu();

// 插入菜单
int insertMenu();

void action(int menu);

void exitAction();

void displayLine(int lineNum);

void deleteLine(int lineNum);

struct line *findLineBy(int lineNum);

void save(char *filename);

void displayAll();

int main() {
    filename = "/Users/cg/data/code/wheel/c/notepad/t";
    do {
        if (DEBUG) {
            time_t lt = time(NULL);
            printf("0==%s==time====%ld\n", __FUNCTION__, lt);
        }
        loadFile(filename);
        int c = firstMenu();
        action(c);
    } while (1);

    return 0;
}

void action(int menu) {
    char *targetLineNumTmp = (char *) malloc(sizeof(char) * 3);
    switch (menu) {
        case 1:
            // 显示
            printf("请输入行号：\n");
            scanf("%s", targetLineNumTmp);
            targetLineNum = atoi(targetLineNumTmp);
            displayLine(targetLineNum);
            break;
        case 2:
            // 插入
            break;
        case 3:
            // 删除
            printf("请输入行号：\n");
//            scanf("%s", targetLineNumTmp);
//            targetLineNum = atoi(targetLineNumTmp);
            targetLineNum = 1;
            deleteLine(targetLineNum);
            if (DEBUG) {
                time_t lt = time(NULL);
                printf("3==%s==time====%ld\n", __FUNCTION__, lt);
            }
            break;
        case 4:
            //保存
            break;
        case 5:
            // 退出
            exitAction();
            break;
        case 6:
            displayAll();
            break;
        case 7:
            loadFile(filename);
            break;
        default:
            printf("菜单输入错误\n");
    }
}

void exitAction() {
    printf("退出\n");
    exit(0);
}

// todo 优化。低效。
void displayLine(int lineNum) {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    if (DEBUG) {
        printf("lineNum = %d\n", lineNum);
    }
    struct line *targetLine = findLineBy(lineNum);
    if (targetLine) {
        printf("%d\t%s", lineNum, targetLine->text);
    } else {
        printf("错误行数%d\n", lineNum);
    }
}

struct line *findLineBy(int lineNum) {
    struct line *targetLine = NULL;
    struct line *info = start;
    if (DEBUG) {
        printf("%s======%s===%d=\n", __FUNCTION__, start->text, start->num);
        printf("%s======%s==%d==\n", __FUNCTION__, last->text, last->num);
        printf("%s==info====%s===%d=\n", __FUNCTION__, info->text, last->num);
    }
    while (info) {
        if (info->num == lineNum) {
            targetLine = info;
            break;
        }
        info = info->next;
    }
    free(info);
    if (DEBUG) {
        printf("%s===end===%s========\n", __FUNCTION__, targetLine->text);
    }
    return targetLine;
}

// todo 没有处理行数
void deleteLine(int lineNum) {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    struct line *targetLine = findLineBy(lineNum);
    // 首行
    if (lineNum == 1) {
        start = (struct line *) malloc(sizeof(struct line));
        start = targetLine->next;
        if (start) {
            start->prior = NULL;
        }
        save(filename);
        return;
    }
    // 尾行
    if (lineNum == last->num) {
        last = targetLine->prior;
        last->next = NULL;
        save(filename);
        return;
    }
    // 其他
    if (targetLine->prior->num == start->num) {
        start->next = targetLine->next;
    } else if (targetLine->next->num == last->num) {
        last->prior = targetLine->prior;
    } else {
        targetLine->prior->next = targetLine->next;
        targetLine->next->prior = targetLine->prior;
    }
    save(filename);
    return;
}

void save(char *filename) {
    FILE *fp = fopen(filename, "w");
    char *str;
    struct line *info = start;
    if (DEBUG) {
        time_t lt = time(NULL);
        printf("5==%s==time====%ld\n", __FUNCTION__, lt);
        printf("0==%s==%s==%d\n", __FUNCTION__, start->text, start->num);
        printf("0==%s==%s==%d\n", __FUNCTION__, last->text, last->num);
    }
    while (info) {
        if (DEBUG) {
            printf("%s==info->text====%s", __FUNCTION__, info->text);
        }
        str = info->text;
        while (*str != '\n') {
            fputc(*str, fp);
            str++;
        }
        fputc('\n', fp);
        if (DEBUG) {
            printf("2==%s==info->text====%s", __FUNCTION__, info->text);
        }
        info = info->next;
        if (DEBUG) {
            time_t lt;
            lt = time(NULL);
            printf("3==%s==time====%ld\n", __FUNCTION__, lt);
//            printf("3==%s==info->text====%s", __FUNCTION__, info->text);
        }
    }
    if (DEBUG) {
        time_t lt = time(NULL);
        printf("4==%s==time====%ld\n", __FUNCTION__, lt);
    }
    fclose(fp);
//    free(info);
//    free(str);
}

int firstMenu() {
    int no;
    char *c = (char *) malloc(sizeof(char) * 100);
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
    return no;
}

int insertMenu() {
    int c;
    printf("\n\t1.插入一行文字\n");
    printf("\t2.插入一段文字\n");
    printf("\t3.返回上级菜单\n");
    do {
        printf("\t请按数字选择：\n");
        scanf("%d", &c);
    } while (!(1 <= c && c <= 3));
    return c;
}

void loadFile(char *filename) {
    lineNum = 0;
    struct line *tmp, *info;
    start = (struct line *) malloc(sizeof(struct line));
    info = start;
    char c;
    FILE *fp = fopen(filename, "r");
    tmp = NULL;
    if (DEBUG) {
        printf("-1=start=%s==%d==\n", __FUNCTION__, start->num);
        time_t lt = time(NULL);
        printf("-1==%s==time====%ld\n", __FUNCTION__, lt);
    }
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (DEBUG) {
            time_t lt = time(NULL);
            printf("while==%s==time====%ld\n", __FUNCTION__, lt);
        }
        int i = 0;
        info->text[i] = c;
        i++;
        while ((c = fgetc(fp)) != '\n' && c != EOF) {
            info->text[i] = c;
            i++;
        }
        if (c != EOF) {
            info->text[i] = '\n';
        }

        lineNum++;
        info->num = lineNum;
        info->next = (struct line *) malloc(sizeof(struct line));
        if (!info->next) {
            printf("\n内存已经用完了\n");
            exit(0);
        }
        info->prior = tmp;
        tmp = info;
        info = info->next;
    }
    if (tmp == NULL) {
        fclose(fp);
        start = NULL;
        last = NULL;
        return;
    }
    if (DEBUG) {
        printf("0=start=%s==%d==\n", __FUNCTION__, start->num);
        printf("0=last=%s==%d==\n", __FUNCTION__, tmp->num);
        time_t lt = time(NULL);
        printf("0==%s==time====%ld\n", __FUNCTION__, lt);
    }
    if (DEBUG) {
        time_t lt = time(NULL);
        printf("3==%s==time====%ld\n", __FUNCTION__, lt);
    }
    tmp->next = NULL;
    if (DEBUG) {
        time_t lt = time(NULL);
        printf("3.5==%s==time====%ld\n", __FUNCTION__, lt);
    }
    last = tmp;
    if (DEBUG) {
        time_t lt = time(NULL);
        printf("4==%s==time====%ld\n", __FUNCTION__, lt);
    }
    start->prior = NULL;
    if (DEBUG) {
        time_t lt = time(NULL);
        printf("5==%s==time====%ld\n", __FUNCTION__, lt);
    }
    free(info);
    if (DEBUG) {
        time_t lt = time(NULL);
        printf("6==%s==time====%ld\n", __FUNCTION__, lt);
    }
    fclose(fp);
    if (DEBUG) {
        printf("%s==start==%s\n", __FUNCTION__, start->text);
        printf("%s==last==%s\n", __FUNCTION__, last->text);
        printf("start===%s====%d\n", start->text, start->num);
        printf("last===%s====%d\n", last->text, last->num);
    }
}

void displayAll() {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    struct line *info;
    info = start;
    while (info) {
        printf("%s", info->text);
        info = info->next;
    }
}