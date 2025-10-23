#include <stdio.h>

struct student {
    char fname[20];
    char lname[20];
    char phone[15];
};

int main(void) {
    struct student list[4];
    struct student *p;  
    int i;

    for (i = 0; i < 4; i++) {
        printf("\nEnter first name: ");
        scanf("%19s", list[i].fname);

        printf("Enter last name: ");
        scanf("%19s", list[i].lname);

        printf("Enter phone in 123-4567 format: ");
        scanf("%14s", list[i].phone);
    }

    printf("\n");

    p = list;

    for (i = 0; i < 4; i++) {
        printf("At address %p: %s %s\tPhone: %s\n",
               (void*)p, p->fname, p->lname, p->phone);
        p++;
    }

    return 0;
}
