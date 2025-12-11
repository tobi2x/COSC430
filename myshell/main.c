#include "shell.h"

int main() {
    // Handle CTRL-C gracefully
    signal(SIGINT, sigint_handler);

    char input[MAX_INPUT];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            printf("\n");
            break;
        }

        // Strip newline
        input[strcspn(input, "\n")] = 0;

        // Ignore empty input
        if (strlen(input) == 0) continue;

        Command cmds[MAX_CMDS];
        int cmd_count = parse_input(input, cmds);

        if (cmd_count > 0) {
            execute_commands(cmds, cmd_count);
        }
    }

    return 0;
}
