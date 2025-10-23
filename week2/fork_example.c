#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t piD = fork();

    if (piD < 0){
        perror("Fork failed to spawn child process");
    }

    printf("%d",piD);
}