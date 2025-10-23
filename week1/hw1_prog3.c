#include <stdio.h>
#include <stdlib.h>

int main() {
    int age;

    printf("Enter your age: ");
    if (scanf("%d", &age) < 0) {
        printf("Invalid input!\n");
        exit(1);
    }

    if (age < 0) {
        printf("Age cannot be negative!\n");
        exit(2);  
    }

    printf("You entered age: %d\n", age);
    exit(0);  
}
