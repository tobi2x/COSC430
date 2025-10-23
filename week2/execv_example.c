#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    char *args[] = {"/bin/ls", NULL, NULL}; 
    execv(args[0], args);
}