#include <stdlib.h> /* uint */

/**
 * `Token` typedef
 * Means: char* (string)
 */
typedef char* Token;

/*
 * Won't document:
 */
int main(int argv, char **args);

/*
 * Need to document:
 */
#define PROMPT_STRING_BUFSIZE 64
char *prompt_alloc(int last_code);
uint tokenizer_token_array_len(Token *array);
int processer_process_args(char *parent_name, int argv, Token *args);

/**
 * tokenizer_read_line()
 * Returns: string (char*)
 */
#define TOKENIZER_READ_LINE_BUFSIZE 512
char *tokenizer_read_line();

/**
 * tokenizer_parse_str(char *str)
 * File: tokenizer.c
 * Returns: NULL-terminated token array (Token*)
 */
#define TOKENIZER_PARSE_STR_BUFSIZE 512
#define TOKENIZER_PARSE_STR_DELIM " \t"
Token *tokenizer_parse_str(char *str);

/*
 * Builtins:
 * For all of these, argv does not include the command name in the size, but the args list contains it.
 */
int builtins_exit(int argv, char **args);
int builtins_chdir(int argv, char **args);
int builtins_pwd(int argv, char **args);
