// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <string.h>

// int main() {
//     int pipefd[2];
//     pid_t pid;

//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(1);
//     }

//     pid = fork();

//     if (pid == 0) {
//         close(pipefd[1]);

//         char buffer[100];
//         int bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
//         buffer[bytes] = '\0';

//         printf("Received message: %s\n", buffer);
//         exit(0);
//     } 
//     else if (pid > 0) {
//         close(pipefd[0]);

//         char message[] = "hey from parent\n";
//         write(pipefd[1], message, strlen(message));

//         close(pipefd[1]);

//         printf("Parent sent: %s\n", message);
//         exit(0);
//     } 
//     else {
//         perror("fork");
//         exit(1);
//     }

//     return 0;
// }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define MAX_CHILDREN 10
#define BUFFER_SIZE 256

typedef struct {
    pid_t pid;
    int   write_fd; 
    int   alive;
} Child;

static Child children[MAX_CHILDREN];
static int num_children = 0;

static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n && s[n-1] == '\n') s[n-1] = '\0';
}

static void reap_children(void) {
    int status;
    pid_t p;
    while ((p = waitpid(-1, &status, WNOHANG)) > 0) {
        // mark dead and close fd
        for (int i = 0; i < num_children; ++i) {
            if (children[i].pid == p && children[i].alive) {
                children[i].alive = 0;
                if (children[i].write_fd >= 0) {
                    close(children[i].write_fd);
                    children[i].write_fd = -1;
                }
                fprintf(stderr, "[info] child %d exited.\n", p);
            }
        }
    }
}

static void gc_children(void) {
    int w = 0;
    for (int r = 0; r < num_children; ++r) {
        if (children[r].alive) {
            if (w != r) children[w] = children[r];
            ++w;
        } else {
            // already closed in reap
        }
    }
    num_children = w;
}

static void show_menu(void) {
    printf("\n=== Message Passing System (Parent) ===\n");
    printf("1. Create a new child process\n");
    printf("2. Send a message to a child (by PID)\n");
    printf("3. Send a message to all children\n");
    printf("4. List all child PIDs\n");
    printf("5. Exit\n");
    printf("Enter your choice (1-5): ");
    fflush(stdout);
}

static void create_child(void) {
    if (num_children >= MAX_CHILDREN) {
        printf("Reached MAX_CHILDREN.\n");
        return;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid == 0) {
        close(pipefd[1]);

        char buf[BUFFER_SIZE];
        ssize_t n;
        printf("[child %d] ready\n", getpid());
        fflush(stdout);
        while ((n = read(pipefd[0], buf, sizeof(buf)-1)) > 0) {
            buf[n] = '\0';
            printf("[child %d] received: %s\n", getpid(), buf);
            fflush(stdout);
        }

        if (n < 0) {
            fprintf(stderr, "[child %d] read error: %s\n", getpid(), strerror(errno));
        } else {
            // EOF
            // printf("[child %d] pipe closed, exiting.\n", getpid());
        }

        close(pipefd[0]);
        _exit(0);
    } else {
        close(pipefd[0]);

        children[num_children].pid = pid;
        children[num_children].write_fd = pipefd[1];
        children[num_children].alive = 1;
        num_children++;

        printf("Child process %d created successfully.\n", pid);
    }
}

static int find_child_index_by_pid(pid_t pid) {
    for (int i = 0; i < num_children; ++i) {
        if (children[i].pid == pid && children[i].alive) return i;
    }
    return -1;
}

static void send_to_child_by_pid(void) {
    char line[128];
    printf("Enter the PID of the child to send to: ");
    fflush(stdout);
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Input error.\n");
        return;
    }
    char *end = NULL;
    long v = strtol(line, &end, 10);
    if (end == line || v <= 0) {
        printf("Invalid PID.\n");
        return;
    }
    pid_t target = (pid_t)v;

    int idx = find_child_index_by_pid(target);
    if (idx < 0) {
        printf("Child with PID %d not found or not alive.\n", target);
        return;
    }

    char msg[BUFFER_SIZE];
    printf("Enter message to send: ");
    fflush(stdout);
    if (!fgets(msg, sizeof(msg), stdin)) {
        printf("Input error.\n");
        return;
    }
    trim_newline(msg);

    ssize_t w = write(children[idx].write_fd, msg, strlen(msg));
    if (w < 0) {
        printf("Write failed: %s\n", strerror(errno));
    } else {
        printf("Sent message to child %d.\n", children[idx].pid);
    }
}

static void send_to_all_children(void) {
    if (num_children == 0) {
        printf("No children to send to.\n");
        return;
    }
    char msg[BUFFER_SIZE];
    printf("Enter message to send to all children: ");
    fflush(stdout);
    if (!fgets(msg, sizeof(msg), stdin)) {
        printf("Input error.\n");
        return;
    }
    trim_newline(msg);

    int sent = 0;
    for (int i = 0; i < num_children; ++i) {
        if (!children[i].alive) continue;
        ssize_t w = write(children[i].write_fd, msg, strlen(msg));
        if (w >= 0) {
            printf("Sent to child %d.\n", children[i].pid);
            sent++;
        } else {
            printf("Failed to send to child %d: %s\n", children[i].pid, strerror(errno));
        }
    }
    if (!sent) printf("No alive children to send to.\n");
}

static void list_children(void) {
    if (num_children == 0) {
        printf("No children are currently tracked.\n");
        return;
    }
    printf("Tracked children:\n");
    for (int i = 0; i < num_children; ++i) {
        printf("  [%d] PID=%d  %s\n", i+1, children[i].pid, children[i].alive ? "alive" : "dead");
    }
}

int main(void) {
    signal(SIGPIPE, SIG_IGN);

    char line[64];
    printf("Welcome to the Message Passing System!\n");

    for (;;) {
        reap_children();
        gc_children();

        show_menu();
        if (!fgets(line, sizeof(line), stdin)) break;
        trim_newline(line);

        char *end = NULL;
        long choice = strtol(line, &end, 10);
        if (end == line) {
            printf("Invalid input. Enter a number 1-5.\n");
            continue;
        }

        switch (choice) {
            case 1: create_child(); break;
            case 2: send_to_child_by_pid(); break;
            case 3: send_to_all_children(); break;
            case 4: list_children(); break;
            case 5:
                printf("Exiting...\n");
                for (int i = 0; i < num_children; ++i) {
                    if (children[i].write_fd >= 0) close(children[i].write_fd);
                }
                while (waitpid(-1, NULL, 0) > 0) {}
                return 0;
            default:
                printf("Invalid choice. Please enter 1-5.\n");
        }
    }
    return 0;
}
