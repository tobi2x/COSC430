#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT 1024
#define MAX_ARGS 128
#define MAX_CMDS 16

// Parsed command structure
typedef struct {
    char *argv[MAX_ARGS];
    char *input_file;
    char *output_file;
    int append;          // >> mode
} Command;

// Function declarations
void sigint_handler(int sig);
int parse_input(char *input, Command *cmds);
int execute_commands(Command *cmds, int cmd_count);
int run_builtin(Command *cmd);

#endif
