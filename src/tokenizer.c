#include <stdio.h>
#include <string.h>

#include "main.h"

char *tokenizer_read_line() {
	uint bufsize = TOKENIZER_READ_LINE_BUFSIZE;
	char *buffer;

	/* try to allocate buffer */
	buffer = malloc((sizeof *buffer) * bufsize);
	if (!buffer) return NULL;

	for (uint pos = 0;; pos++) {
		/* realloc if buffer is full already */
		if (pos >= bufsize) {
			bufsize += TOKENIZER_READ_LINE_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer) return NULL;
		}

		int c = getchar();
		if (c == '\n') {
			buffer[pos] = '\0';
			return buffer;
		} else if (c == EOF) {
			/* STDIN is closed */
			return NULL;
		} else {
			buffer[pos] = c;
		}
	}
}

Token *tokenizer_parse_str(char *str) {
	uint bufsize = TOKENIZER_PARSE_STR_BUFSIZE;
	Token *tokens, token;
	uint pos = 0;

	/* alloc enough for TOKENIZER_PARSE_STR_BUFSIZE tokens */
	tokens = malloc((sizeof token) * bufsize);
	if (!tokens) return NULL;

	token = strtok(str, TOKENIZER_PARSE_STR_DELIM);
	while (token) {
		tokens[pos] = token;
		pos++;

		/* reallocate if pos overflows buffer */
		if (pos >= bufsize) {
			bufsize += TOKENIZER_PARSE_STR_BUFSIZE;
			tokens = realloc(tokens, (sizeof token) * bufsize);
			if (!tokens) return NULL;
		}

		/* continue tokenizing */
		token = strtok(NULL, TOKENIZER_PARSE_STR_DELIM);
	}

	tokens[pos] = NULL;
	return tokens;
}

uint tokenizer_token_array_len(Token *array) {
	uint size;
	for (size = 0; array[size]; size++);
	return size;
}
