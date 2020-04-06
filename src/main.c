#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "shell.h"

#define PROMPT_STRING_BUFSIZE 64

int main(void);
char *promptalloc(int status);

int main() {
    int status = 0;
    char *prompt;

    for (;;) {
        char *input;
        char **tokens;

        prompt = promptalloc(status);
        printf(prompt);

        input = get_input();
        tokens = tokenize_input(input);
        status = run_command(tokens);

        free(input);
        free(tokens);
        free(prompt);
    }

    return EXIT_SUCCESS;
}

char *promptalloc(int status) {
    char *prompt;

    /* Allocate space for the prompt */
    prompt = malloc(sizeof(char) * PROMPT_STRING_BUFSIZE);
    if (!prompt) {
        fprintf(stderr, "prompt allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* Try to make the exit code part of the prompt, if it's not zero */
    if (status) {
        char exit_code_str[8];
        sprintf(exit_code_str, "[%d]", status);
        if (!strlen(exit_code_str)) {
            fprintf(stderr, "prompt exit code parsing error\n");
            exit(EXIT_FAILURE);
        }
        strcat(prompt, exit_code_str);
    }

    strcat(prompt, "> ");

    return prompt;
}
