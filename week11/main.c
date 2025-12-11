// main.c
#include <stdio.h>
#include "process_lib.h"

int main(void) {
    int pid = create_process();
    if (pid == 0) {
        printf("Hello from child!\n");
    } else if (pid > 0) {
        printf("Hello from parent!\n");
    }
    return 0;
}
