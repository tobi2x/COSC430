#include <stdio.h>

struct student {
    char fname[20];
    char lname[20];
    char phone[11]; 
};

int main(){
    struct student list[4];
    int i;

    for (i = 0; i < 4; i++) {
        printf("\nEnter first name: ");
        scanf("%s", list[i].fname);

        printf("Enter last name: ");
        scanf("%s", list[i].lname);

        printf("Enter phone in 123-4567 format: ");
        scanf("%s", list[i].phone);
    }

    printf("\n");

    for (i = 0; i < 4; i++) {
        printf("Name: %s %s\tPhone: %s\n",
               list[i].fname, list[i].lname, list[i].phone);
    }

    return 0;
}
