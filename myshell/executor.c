#include "shell.h"

void sigint_handler(int sig) {
    // Don't kill shell, just print a newline
    printf("\nmyshell> ");
    fflush(stdout);
}

int run_builtin(Command *cmd) {
    if (cmd->argv[0] == NULL)
        return 1;

    if (strcmp(cmd->argv[0], "cd") == 0) {
        if (cmd->argv[1] == NULL)
            chdir(getenv("HOME"));
        else
            chdir(cmd->argv[1]);
        return 1;
    }

    if (strcmp(cmd->argv[0], "exit") == 0) {
        exit(0);
    }

    return 0; // Not a builtin
}

int execute_commands(Command *cmds, int cmd_count) {
    int pipes[2], in_fd = 0;

    for (int i = 0; i < cmd_count; i++) {
        // Built-in with no pipes
        if (cmd_count == 1 && run_builtin(&cmds[i]))
            return 0;

        pipe(pipes);
        pid_t pid = fork();

        if (pid == 0) {
            // CHILD PROCESS

            // Handle input redirection
            if (cmds[i].input_file) {
                int fd = open(cmds[i].input_file, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                close(fd);
            } else if (in_fd != 0) {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Handle output redirection
            if (cmds[i].output_file) {
                int fd;
                if (cmds[i].append)
                    fd = open(cmds[i].output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                else
                    fd = open(cmds[i].output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                dup2(fd, STDOUT_FILENO);
                close(fd);
            } else if (i < cmd_count - 1) {
                dup2(pipes[1], STDOUT_FILENO);
            }

            close(pipes[0]);
            close(pipes[1]);

            execvp(cmds[i].argv[0], cmds[i].argv);
            perror("execvp");
            exit(1);
        }

        // PARENT PROCESS
        waitpid(pid, NULL, 0);
        close(pipes[1]);

        if (in_fd != 0)
            close(in_fd);

        in_fd = pipes[0];
    }

    return 0;
}
