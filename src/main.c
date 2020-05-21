#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main(int argv, char** args) {
	int last_code = 0; /* last program's exit code */
	char *prompt;

	if (argv != 1)
		printf("%s: warning: argument parsing is not a feature yet\n", args[0]);

	for (;;) {
		char *input;
		char **tokens;

		/* make and print prompt */
		prompt = prompt_alloc(last_code);
		printf("%s", prompt);

		/* get input */
		input = tokenizer_read_line();
		if (!input) {
			printf("%s: could not read line", args[0]);
			return EXIT_FAILURE;
		}

		/* parse input */
		tokens = tokenizer_parse_str(input);
		if (!tokens) {
			printf("%s: could not parse line", args[0]);
			return EXIT_FAILURE;
		}

		/* get amount of tokens */
		int command_argv = tokenizer_token_array_len(tokens);
		last_code = processer_process_args(args[0], command_argv, tokens);

		/* free some things */
		free(prompt);
		free(tokens);
		free(input);
	}
}

char *prompt_alloc(int last_code) {
	char *prompt;

	/* alloc space for prompt, return NULL if failed */
	prompt = malloc((sizeof *prompt) * PROMPT_STRING_BUFSIZE);
	if (!prompt)
		return NULL;

	/* if not zero, put the exit code part of the prompt */
	if (last_code != 0) {
		/* this part seems very flawled. Might take a look at the stdlib and see what string commands use malloc. */
		char str[8];
		sprintf(str, "[%d]", last_code);
		if (strlen(str) == 0)
			return NULL;
		strcat(prompt, str);
	}
	
	strcat(prompt, "> ");
	return prompt;
}
