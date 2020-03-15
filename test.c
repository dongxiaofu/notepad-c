#include <stdio.h>
#include <stdlib.h>

struct List {
    int v;
//    struct List *prior;
    struct List *next;
};

int main() {
    struct List list3 = {3, NULL};
    struct List list2 = {2, &list3};
    struct List list1 = {1, &list2};


    struct List *p;
    p = &list1;
    while (p) {
        printf("v = %d\n", p->v);
        p = p->next;
    }

    list2.v = 23;

    struct List *p2;
    p2 = &list1;
    while (p2) {
        printf("v = %d\n", p2->v);
        p2 = p2->next;
    }

    struct List *p3 = (struct List *)malloc(sizeof(struct List));
    struct List *p4 = (struct List *)malloc(sizeof(struct List));
    p4 = &list2;
    p4->v = 78;
    printf("p4.v = %d\n", p4->v);
    p3 = &list1;
    while(p3){
        printf("p3v = %d\n", p3->v);
        p3 = p3->next;
    }


    return 0;
}
