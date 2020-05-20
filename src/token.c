#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

char *get_input() {
    int bufsize = GET_INPUT_BUFSIZE;
    int position = 0; /* TODO: Might be too small someday, so fix it!!!! Also, it needs to be zero... I thought its default value was zero, but it seems that it gives a segmentation fault if acessed. Or not... well, I need to look into this later. */
    char *buffer;
    int c;

    /* Try to allocate a buffer */
    buffer = malloc(sizeof(char) * bufsize);
    if (!buffer) {
        fprintf(stderr, "line allocation error\n");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        c = getchar();

        if (c == EOF || c == '\n') {
            /* FIXME: pressing ^D on an empty line causes an infinite loop. Don't know why. */
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }

        position++;

        /* Reallocate if buffer is full already */
        if (position >= bufsize) {
            bufsize += GET_INPUT_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if (!buffer) {
                fprintf(stderr, "line allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/* This function doesn't support quotes and escape characters yet. :( */
char **tokenize_input(char *input) {
    int bufsize = PARSE_ARGS_BUFSIZE;
    int position = 0;
    char **tokens, *token;

    /* Allocate enough for PARSE_ARGS_BUFSIZE tokens */
    tokens = malloc(bufsize * sizeof(char*));
    if (!tokens) {
        fprintf(stderr, "tokenizer allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* Tell to strtok which string to tokenize and get first token */
    token = strtok(input, PARSE_ARGS_TOK_DELIM);
    while (token) {
        tokens[position] = token;
        position++;

        /* Reallocate if position overflows the buffer */
        if (position >= bufsize) {
            bufsize += PARSE_ARGS_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "parser allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        /* Null here means that strtok will keep tokenizing the string
         * specified before. Quite tricky but interesting. */
        token = strtok(NULL, PARSE_ARGS_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

int tokens_len(char **tokens) {
    int pos;
    for (pos = 0; tokens[pos]; pos++);

    return pos;
}
