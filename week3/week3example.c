#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run_command(char *cmd, char *args[]) {
    if (execv(cmd, args) == -1) {
        perror("execv failed");
        exit(1);
    }
}

int main() {
    int choice;
    char filename[100];

    while (1) {
        printf("1. List files (ls)\n");
        printf("2. Show file contents (cat)\n");
        printf("3. Print working directory (pwd)\n");
        printf("4. Show date and time (date)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char *args[] = {"/bin/ls", NULL};
                run_command("/bin/ls", args);
                break;
            }
            case 2: {
                printf("Enter filename: ");
                scanf("%s", filename);
                char *args[] = {"/bin/cat", filename, NULL};
                run_command("/bin/cat", args);
                break;
            }
            case 3: {
                char *args[] = {"/bin/pwd", NULL};
                run_command("/bin/pwd", args);
                break;
            }
            case 4: {
                char *args[] = {"/bin/date", NULL};
                run_command("/bin/date", args);
                break;
            }
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
