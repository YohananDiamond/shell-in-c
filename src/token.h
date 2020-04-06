char *get_input();
char **tokenize_input(char *input);
int tokens_len(char **tokens);

/* The size that get_input will allocate initially */
#define GET_INPUT_BUFSIZE 512

/* Tokenizer options */
#define PARSE_ARGS_BUFSIZE 64
#define PARSE_ARGS_TOK_DELIM " \t"
