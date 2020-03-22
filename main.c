#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>

#define DEBUG 0
#define FILE_IS_EMPTY "文件为空，请先增加内容"

// 定义布尔类型
#define BOOL int
#define TRUE 1
#define FALSE 0

const int MAX_LEN = 200;
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
// OK
void loadFile(char *filename);

// 一级菜单
int firstMenu();

// 插入菜单
int insertMenu();

// 操作
void action(int menu);

// 退出
void exitAction();

// 显示一行
void displayLine(int lineNum);

// 删除一行
void deleteLine(int lineNum);

// 查找一行
// OK
struct line *findLineBy(int lineNum);

// 保存数据
void save(char *filename, char *mode);

// 显示所有内容
void displayAll();

// 插入功能
void insertFunction();

// 在文件开头插入数据
void insert();

// 追加数据
void add();

// 在指定的行插入数据
void insertInLineNum();

// 在指定行插入一行数据
void insertOneLine();

// 在指定行插入空白行
void insertEmptyLine();

// 获取文件中的所有数据
char *getStrFromFile();

// 查找字符串返回第一个结果
void search();

// 查找字符串返回所有结果
void searchAll();

//字符串替换（一个）
void replace();

//打开文件
char *openFile();
// 检查文件是否存在
BOOL fileExists(char *filename);

// 新建文件
void createFile(char *filename);

// 增删文件后，调整行数
// 需要调整的文件行的起始行；type：0.减，1.加
void repaireLineList(struct line *startLine, int type);
// 自动保存数据
void *bgSave();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage:notepad filename\n");
        return 0;
    }

    filename = (char *) malloc(sizeof(char) * 10);
    filename = argv[1];
    createFile(filename);

    loadFile(filename);

    pthread_t pthread;
    if(pthread_create(&pthread, NULL, bgSave, NULL) < 0){
        perror("pthread create\n");
    }

    do {
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
            insertFunction();
            break;
        case 3:
            // 删除
            printf("请输入行号：\n");
            scanf("%s", targetLineNumTmp);
            targetLineNum = atoi(targetLineNumTmp);
            deleteLine(targetLineNum);
            break;
        case 4:
            //保存
            save(filename, "w");
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
        case 21:
            insert();
            break;
        case 22:
            add();
            break;
        case 24:
            insertInLineNum();
            break;
        case 25:
            insertOneLine();
            break;
        case 26:
            insertEmptyLine();
            break;
        case 27:
            search();
            break;
        case 28:
            searchAll();
            break;
        case 29:
            replace();
            break;
        case 30:
            openFile();
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
    struct line *targetLine = findLineBy(lineNum);
    if (targetLine) {
        printf("%d\t%s", lineNum, targetLine->text);
    } else {
        printf("错误行数%d\n", lineNum);
    }
}

struct line *findLineBy(int linenum) {
    struct line *info6;
    info6 = start;
    while (info6) {
        if (linenum != info6->num) {
//            printf("666%s#####text:%s\n", __FUNCTION__, info6->text);
//            printf("666%s#####num:%d\n", __FUNCTION__, info6->num);
            info6 = info6->next;
        } else {
//            printf("777%s#####text:%s\n", __FUNCTION__, info6->text);
//            printf("777%s#####num:%d\n", __FUNCTION__, info6->num);
            break;
        }
    }
//    printf("2222%s#####text:%s\n", __FUNCTION__, info6->text);
//    printf("2222%s#####num:%d\n", __FUNCTION__, info6->num);
    return (info6);
}

//struct line *findLineBy(int lineNum) {
//    struct line *targetLine = NULL;
////    struct line *info = start;
//    struct line *info = (struct line *) malloc(sizeof(struct line));
//    info = start;
//    printf("000%s#####text:%s\n", __FUNCTION__, start->text);
//    while (info) {
//        if (info->num == lineNum) {
//            targetLine = info;
//            break;
//        }
//        info->next = (struct line *) malloc(sizeof(struct line));
//        if (!info->next) {
//            printf("内存已经用完\n");
//            exit(0);
//        }
//        info = info->next;
//    }
//    printf("1111%s#####text:%s\n", __FUNCTION__, start->text);
//    printf("33333%s#####text:%s\n", __FUNCTION__, targetLine->text);
//    free(info);   // 又导致野指针
////    main(99051,0x10de32dc0) malloc: *** error for object 0x7fe023d00000: pointer being freed was not allocated
////    main(99051,0x10de32dc0) malloc: *** set a breakpoint in malloc_error_break to debug
//    printf("2222%s#####text:%s\n", __FUNCTION__, targetLine->text);
//    return targetLine;
//}

// todo 没有处理行数
void deleteLine(int lineNum) {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    char *mode = "w";
    struct line *targetLine = findLineBy(lineNum);
    // 首行
    if (lineNum == 1) {
        start = (struct line *) malloc(sizeof(struct line));
        start = targetLine->next;
        if (start) {
            start->prior = NULL;
        }
        repaireLineList(start, 0);
//        save(filename, mode);
        return;
    }
    // 尾行
    if (lineNum == last->num) {
        last = targetLine->prior;
        last->next = NULL;
//        save(filename, mode);
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

    repaireLineList(targetLine->next, 0);


//    save(filename, mode);
    return;
}

void save(char *filename, char *mode) {
    if (!mode) {
        mode = "w";
    }
    FILE *fp = fopen(filename, mode);
    char *str;
    struct line *info = start;
    while (info) {
        str = info->text;
        while (*str) {
            fputc(*str, fp);
            str++;
        }
//        fputc('\n', fp);
        info = info->next;
    }
    fclose(fp);
//    free(info);
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
//        printf("\t\t请选择一项功能：\n");

        printf("\t\t21.在开头插入数据\n");
        printf("\t\t22.追加数据\n");
        printf("\t\t23.返回上级菜单\n");
        printf("\t\t24.在选定行插入数据\n");
        printf("\t\t25.在指定行插入一行数据\n");
        printf("\t\t26.在指定行插入空白行\n");
        printf("\t\t27.查找字符串返回第一个结果\n");
        printf("\t\t28.查找字符串返回所有结果\n");
        printf("\t\t29.字符串替换（一个）\n");
        printf("\t\t30.打开文件\n");
        printf("\t\t31.新建文件\n");

        printf("\t\t请按数字选择：\n");

        scanf("%s", c);
        no = atoi(c);
        if ((1 <= no && no <= 99)) {
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
    while (1) {
//        int c = (int)malloc(sizeof(c));
        char *c2;
        int c;
        printf("\n\t1.插入一行文字\n");
        printf("\t2.插入一段文字\n");
        printf("\t3.返回上级菜单\n");
        printf("\t请按数字选择：\n");
//        scanf("%s", c2);
        scanf("%d", &c);
//        printf("%ld\n", time(NULL));
//        printf("c2 = %s\n", c2);
//        int c = atoi(c2);
        if (1 <= c && c <= 3) {
            printf("break\n");
            return c;
        }
    }
}

void loadFile(char *filename) {
    lineNum = 0;
    struct line *tmp;
    char c;
    FILE *fp = fopen(filename, "r");
    tmp = NULL;
    struct line *info = (struct line *) malloc(sizeof(struct line));
    while ((c = fgetc(fp)) != EOF) {
        int i = 0;
        if (c == '\n') {
            info->text[i] = '\n';
        } else {
            info->text[i] = c;
            i++;
            // todo 需要检测c==EOF吗？
            while ((c = fgetc(fp)) != '\n' && c != EOF) {
                info->text[i] = c;
                i++;
            }
            if (c == EOF) {
                printf("EOF:%d\n", c);
            }
            // 空行如何识别？空行是10#10
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
        if (tmp->num == 1) {
            start = info;
        }

        info = info->next;
    }
    if (tmp == NULL) {
        fclose(fp);
        start = NULL;
        last = NULL;
        return;
    }

    tmp->next = NULL;
    last = tmp;

    struct line *info6;
    start->prior = NULL;
    info6 = start;
    free(info);
    fclose(fp);
}

void displayAll() {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    struct line *info;
    info = start;
    while (info) {
        printf("%d %s", info->num, info->text);
        info = info->next;
    }
}

void insertFunction() {
    int type = insertMenu();
    switch (type) {
        case 21:
            // 插入一行文字
            insert();
            break;
        case 22:
            // 插入一段文字
            break;
        case 23:
            // 返回上级菜单
            break;
    }
}

// 插入之后，只有一行，last等于start吗？
// start 必须明确，last可以模糊
// start 与 last 值相同，但指向不同
void insert() {
    char *str = (char *) malloc(sizeof(char) * MAX_LEN);
    printf("输入数据：\n");
    scanf("%s", str);
    char *text = (char *) malloc(sizeof(char) * MAX_LEN);
    memcpy(text, str, strlen(str));
    fgets(str, MAX_LEN, stdin);
    strcat(text, str);
    struct line *newLine = (struct line *) malloc(sizeof(struct line));
    strcpy(newLine->text, text);
    newLine->prior = NULL;
    newLine->next = start;
    newLine->num = 1;
    // 处理起来费事。
    if(start == NULL){
        start = last = newLine;
    }else{
        start->prior = newLine;
        if(last->prior == NULL){
            last->prior = start;
        }
        start = newLine;
    }
    repaireLineList(start->next, 1);

    return;
//
//    char *str2 = getStrFromFile();
//    FILE *fp = fopen(filename, "w");
//    fputs(str, fp);
//    // 与上面的scanf结合使用，完整接收"how are you"这种有空格的数据；
//    // 若没有scanf，不会阻塞等待用户输入数据。
//    fgets(str, MAX_LEN, stdin);
////    gets(str);
//    fputs(str, fp);
////    fputc('\n', fp);
//
//    fputs(str2, fp);
//    fclose(fp);
//    save(filename, "a");
//    free(str);
}

void add() {
    char *str = (char *) malloc(sizeof(char) * MAX_LEN);
    printf("请输入数据：\n");
    scanf("%s", str);
    char *text = (char *) malloc(sizeof(char) * MAX_LEN);
    // 能够使用 strcpy 吗？
    memcpy(text, str, strlen(str));
    printf("0#####text = %s######str = %s\n", text, str);
    fgets(str, MAX_LEN, stdin);
    strcat(text, str);
    printf("1#####text = %s######str = %s\n", text, str);
    struct line *newLine = (struct line *) malloc(sizeof(struct line));
    memcpy(newLine->text, text, strlen(text));
    newLine->prior = last;
    newLine->next = NULL;
    if(last == NULL){
        newLine->num = 1;
        start = last = newLine;
    }else{
        if(start->next == NULL){
            start->next = newLine;
        }
        newLine->num = last->num + 1;
        last = newLine;
    }

    free(newLine);
    newLine = NULL;

    // 旧方法
//    char *str = (char *) malloc(sizeof(char) * MAX_LEN);
//    printf("请输入数据：\n");
//    scanf("%s", str);
//    FILE *fp = fopen(filename, "a");
//    fputs(str, fp);
//    fgets(str, MAX_LEN, stdin);
//    fputs(str, fp);
//    fclose(fp);
//    free(str);
}

void insertInLineNum() {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    printf("请输入行数：");
    int lineNum;
    scanf("%d", &lineNum);
    printf("请输入列数：\n");
    int rowNum;
    scanf("%d", &rowNum);
    struct line *targetLine = findLineBy(lineNum);
    if (targetLine == NULL) {
        printf("第%d行第%d列不存在\n", lineNum, rowNum);
        return;
    }
    printf("请输入数据：\n");
    char *text = targetLine->text;
    int textRowNum = targetLine->num;
    int textLength = strlen(text);

    // 要插入的位置比目标行的长度长
    if (rowNum > textLength) {
        char *str = (char *) malloc(sizeof(char) * MAX_LEN);
        scanf("%s", str);
        char *emptyStr = " ";
        // 去掉换行符
        strcpy(&text[textLength - 1], emptyStr);
        for (int i = 0; i < rowNum - textLength - 1; i++) {
            strcat(text, emptyStr);
        }
        strcat(text, str);
        char *str2 = (char *) malloc(sizeof(char) * MAX_LEN);
        fgets(str2, MAX_LEN, stdin);
        strcat(text, str2);
        // free 操作是否必要？
//        free(emptyStr);
//        free(str);
//        free(str2);
    } else {// 要插入的位置在目标行的中间
        char *str = (char *) malloc(sizeof(char) * MAX_LEN);
        scanf("%s", str);
        char *cache = (char *) malloc(sizeof(char) * MAX_LEN);
        strcpy(cache, &text[rowNum - 1]);
        strcpy(&text[rowNum - 1], str);
        // fgets与上面的scanf，若都使用str，此处会出现Segmentation fault: 11。
        // 在其他地方，同样场景，又不会出现此错误。原因未知。
        char *str2 = (char *) malloc(sizeof(char) * MAX_LEN);
        fgets(str2, MAX_LEN, stdin);
        char trimedLFStr[strlen(str2) - 1];
        int i = 0;
        while (*str2 != '\n') {
            trimedLFStr[i++] = *str2++;
        }
        strcat(text, trimedLFStr);
        strcat(text, cache);
        free(str);
        str = NULL;
        free(cache);
        cache = NULL;
    }
//    // 文件存盘
//    save(filename, "w");
//    // 目标行已经被修改，需要把它放进原来的链表中吗？回答是：不需要。
}

void insertOneLine() {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    printf("输入行号:\n");
    int lineNum;
    scanf("%d", &lineNum);
    struct line *targetLine = findLineBy(lineNum);
    if (targetLine == NULL) {
        printf("不存在%d行\n", lineNum);
        return;
    }
    printf("输入数据:\n");
    char *str = (char *) malloc(sizeof(char) * MAX_LEN);
    scanf("%s", str);
    char *str2 = (char *) malloc(sizeof(char) * MAX_LEN);
    printf("0str2 = %s\n", str2);
    fgets(str2, MAX_LEN, stdin);
    char *newStr = (char *) malloc(sizeof(char) * MAX_LEN);
    strcat(newStr, str);
    strcat(newStr, str2);
    printf("str = %s\nstr2 = %s\n", str, str2);
    struct line *newLine = (struct line *) malloc(sizeof(struct line));
    newLine->num = targetLine->num;
    strcpy(newLine->text, newStr);
    printf("newStr = %s\n", newStr);
    // 此处的链表操作，容易出现死循环
    newLine->prior = targetLine->prior;
    printf("targetLine->prior:%p\n", targetLine->prior);
    newLine->next = targetLine;
    if (targetLine->prior) {
        targetLine->prior->next = newLine;
    }
    targetLine->prior = newLine;
    if (targetLine->num == 1) {
        start = newLine;
    }
    free(newLine);
    newLine = NULL;

    // 在此操作之后，能释放掉targetLine吗？
    repaireLineList(targetLine, 1);

//    struct line *info2;
//    info2 = start;
//    int i = 0;
//    while (info2) {
//        info2 = info2->next;
//        i++;
//        if (i == 4) {
//            break;
//        }
//    }
//    save(filename, "w");
}

void insertEmptyLine() {
    if (start == NULL) {
        printf("%s\n", FILE_IS_EMPTY);
        return;
    }
    int lineNum;
    printf("输入行号：\n");
    scanf("%d", &lineNum);
    struct line *targetLine = findLineBy(lineNum);
    if (targetLine == NULL) {
        printf("%s\n", "目标行不存在");
        return;
    }

    struct line *newLine = (struct line *) malloc(sizeof(struct line));
    newLine->text[0] = '\n';

    newLine->num = targetLine->num;
    // 在首行插入
    if (start->num == targetLine->num) {
        newLine->next = targetLine;
        start = newLine;
    } else {
        newLine->next = targetLine;
        newLine->prior = targetLine->prior;
        targetLine->prior->next = newLine;
        targetLine->prior = newLine;
    }

    repaireLineList(targetLine, 1);
//    struct line *info4;
//    info4 = start;
//    while (info4) {
//        printf("info4:%s\n", info4->text);
//        info4 = info4->next;
//    }

//    save(filename, "w");
}

char *getStrFromFile() {
    char *str = (char *) malloc(sizeof(char) * MAX_LEN);
    if (start == NULL) {
        return str;
    }
    struct line *info;
    info = start;
    while (info) {
        strcat(str, info->text);
        info = info->next;
        if (info) {
            str = (char *) realloc(str, sizeof(char) * MAX_LEN);
        }
    }

    return str;
}

void search() {
    char *str = (char *) malloc(sizeof(char) * 10);
    printf("输入关键词：\n");
    scanf("%s", str);
    printf("str:%s\n", str);
    if (strlen(str) == 0) {
        printf("关键词不能为空\n");
        return;
    }
    int strLen = strlen(str);
    struct line *info7 = start;
    printf("start:%s\n", start->text);
    while (info7) {
        int k;
        int length = strlen(info7->text);
        printf("length:%d\n", length);
        for (int i = 0; i < length; i++) {
            k = i;
            int j;
            for (j = 0; j < strLen; j++) {
                if (str[j] != info7->text[k++]) {
                    break;
                }
            }
            if (j == strLen) {
                printf("字符串：%s在第%d行第%d列第一次出现\n", str, info7->num, k - strLen + 1);
                return;
            }
        }
        info7 = info7->next;
    }
    printf("没有查找到字符串：%s\n", str);
    return;
}

void searchAll() {
    char *str = (char *) malloc(sizeof(char) * 10);
    printf("输入关键词：\n");
    scanf("%s", str);
    int strLen = strlen(str);

    if (strLen == 0) {
        printf("关键词不能为空\n");
        return;
    }
    struct Result {
        int line;        // 行
        int row;         // 列
        int index;       // 序数
        struct Result *next;
    };

    // 不能使用数组，使用链表代替
//    struct Result results[] = {};
    struct line *info7 = start;
    struct Result *result = (struct Result *) malloc(sizeof(struct Result));
    struct Result *head = (struct Result *) malloc(sizeof(struct Result));
    int counter = 0;
    while (info7) {
        int k;
        for (int i = 0; i < strlen(info7->text); i++) {
            k = i;
            int j;
            for (j = 0; j < strLen; j++) {
                if (str[j] != info7->text[k++]) {
                    break;
                }
            }
            // 查找到了目标
            if (j == strLen) {
                result->line = info7->num;
                result->row = k - strLen + 1;
                result->next = (struct Result *) malloc(sizeof(struct Result));
                if (result->next == NULL) {
                    printf("内存不足\n");
                    exit(0);
                }
                counter++;
                result->index = counter;
                if (counter == 1) {
                    head = result;
                }
                result = result->next;
            }
        }
        info7 = info7->next;
    }

    // 最后一个result是没有赋值的
    if (result->index > 0) {
        result->next = NULL;
    }

    printf("字符串 %s 搜索结果：\n", str);
    struct Result *result1 = head;
    // 因为最后一个result是没有赋值的，所有需要 result1->index > 0 排除最后一个
    while (result1 && result1->index > 0) {
        printf("第%d行第%d列\n", result1->line, result1->row);
        result1 = result1->next;
    }
}

void replace() {
    printf("输入关键词:\n");
    char *str = (char *) malloc(sizeof(char) * 10);
    scanf("%s", str);
    int strLen = strlen(str);
    if (strLen == 0) {
        printf("关键词不能为空\n");
        exit(0);
    }
    printf("输入替代关键词：\n");
    char *replaceStr = (char *) malloc(sizeof(char) * 10);
    scanf("%s", replaceStr);
    if (strlen(replaceStr) == 0) {
        printf("替代关键词不能为空\n");
        exit(0);
    }
    typedef struct {
        struct line *line;  // 包含关键词的行
        int position;   // 关键词在目标行的列号
        int flag:1;     // 是否存在搜索结果
    } Result;
    struct line *line = (struct line *) malloc(sizeof(struct line));
    line = start;
    struct line *targetLine = (struct line *) malloc(sizeof(struct line));
    Result *result = (Result *) malloc(sizeof(Result));
    while (line) {
        for (int i = 0; i < strlen(line->text); i++) {
            int k = i;
            int j;
            for (j = 0; j < strLen; j++) {
                if (str[j] != line->text[k++]) {
                    break;
                }
            }

            if (j == strLen) {
                result->line = line;
                result->position = k - strLen;
                result->flag = 1;
                break;
            }
        }
        if (result->flag == 1) {
            break;
        }
        line = line->next;
    }
    if (result->flag == 0) {
        printf("没有查到字符串 %s\n", str);
        return;
    }
    targetLine = result->line;
    int position = result->position;
    // 申请内存远大于所需内存，会造成浪费吗？有方法不这样浪费内存吗？
    char *newStr = (char *) malloc(sizeof(char) * MAX_LEN);
    char *leftCache = (char *) malloc(sizeof(char) * (MAX_LEN / 2));
    char *rightCache = (char *) malloc(sizeof(char) * (MAX_LEN / 2));
    // position的值，涉及到一两个字符，容易弄错。我是举例来确定的。
    strncpy(leftCache, targetLine->text, position);
    printf("leftCache:%s\n", leftCache);
    strcpy(rightCache, &targetLine->text[position + strLen]);
    printf("rightCache:%s\n", rightCache);
    strcpy(newStr, leftCache);
    strcat(newStr, replaceStr);
    strcat(newStr, rightCache);
    // 这种方法，最后会将rightCache指向的数据复制到newStr指向的内存中
//    strcpy(newStr, replaceStr);
//    strcpy(newStr, rightCache);

    printf("处理结果：\n");
    printf("已经将第%d行第%d列的%s替换为%s\n", targetLine->num, position + 1, str, replaceStr);
    printf("新数据为：\n");
    printf("%s\n", newStr);

    // 只需修改这个结点，并不需要再将修改后的结点嵌入文件数据链表中。
    strcpy(targetLine->text, newStr);
    save(filename, "w");
}

char *openFile() {
    printf("输入文件名：\n");
    char *filename1 = (char *) malloc(sizeof(char) * 10);
    filename = filename1;
    scanf("%s", filename);
    if (strlen(filename) == 0) {
        printf("文件名不能为空\n");
        exit(0);
    }
    if (fileExists(filename) == FALSE) {
        printf("文件 %s 不存在\n", filename);
        exit(0);
    }

    return filename;
}

BOOL fileExists(char *filename) {
    if (access(filename, F_OK) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void createFile(char *filename) {
    if (fileExists(filename) == FALSE) {
        FILE *fp = fopen(filename, "w");
        fclose(fp);
    }
}

void repaireLineList(struct line *startLine, int type) {
    struct line *current = (struct line *) malloc(sizeof(struct line));
    current = startLine;
    while (current != NULL) {
        if (type == 0) {
            current->num = current->num - 1;
        } else {
            current->num = current->num + 1;
        }
        current = current->next;
    }

    free(current);
    current = NULL;
}

void *bgSave()
{
    time_t start,current;
    time(&start);
    int duration = 2;
    while (1){
        time(&current);
        if((current - start)%duration == 0){
            printf("保存数据:%ld\n", time(NULL));
            save(filename, "w");
        }
        sleep(20);
    }

}