// process_lib.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "process_lib.h"

int create_process(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return -1;
    } else if (pid == 0) {
        printf("Child process (PID: %d)\n", getpid());
        return 0;
    } else {
        printf("Parent process (PID: %d), child PID: %d\n", getpid(), pid);
        return pid;
    }
}

void print_anything(void *data, char type) {
    switch (type) {
        case 'i': printf("%d\n", *(int*)data); break;
        case 'f': printf("%f\n", *(float*)data); break;
        case 'c': printf("%c\n", *(char*)data); break;
        case 's': printf("%s\n", (char*)data); break;
        default:  printf("Unknown type\n");
    }
}