#include "shell.h"

int parse_input(char *input, Command *cmds) {
    int cmd_index = 0;
    int arg_index = 0;

    cmds[0].argv[0] = NULL;
    cmds[0].input_file = NULL;
    cmds[0].output_file = NULL;
    cmds[0].append = 0;

    char *token = strtok(input, " ");

    while (token != NULL) {
        if (strcmp(token, "|") == 0) {
            // close current command
            cmds[cmd_index].argv[arg_index] = NULL;

            // move to next command
            cmd_index++;
            arg_index = 0;

            cmds[cmd_index].argv[0] = NULL;
            cmds[cmd_index].input_file = NULL;
            cmds[cmd_index].output_file = NULL;
            cmds[cmd_index].append = 0;

        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            cmds[cmd_index].input_file = token;

        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            cmds[cmd_index].output_file = token;
            cmds[cmd_index].append = 0;

        } else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " ");
            cmds[cmd_index].output_file = token;
            cmds[cmd_index].append = 1;

        } else {
            cmds[cmd_index].argv[arg_index++] = token;
        }

        token = strtok(NULL, " ");
    }

    cmds[cmd_index].argv[arg_index] = NULL;
    return cmd_index + 1;
}
