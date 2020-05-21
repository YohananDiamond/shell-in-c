#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "main.h"

int builtins_exit(int argv, char **args) {
	if (argv == 0) {
		exit(EXIT_SUCCESS);
	} else if (argv == 1) {
		int code = (int) strtol(args[1], NULL, 10);
		exit(code);
	} else {
		printf("%s: invalid amount of arguments\n", args[0]);
		return EXIT_SUCCESS;
	}
}

int builtins_chdir(int argv, char **args) {
	char *dirname;

	if (argv == 0) {
		dirname = getenv("HOME");
		if (!dirname) {
			printf("%s: $HOME is not set\n", args[0]);
			return EXIT_FAILURE;
		}
	} else if (argv == 1) {
		dirname = args[1];
	} else {
		printf("%s: invalid amount of arguments\n", args[0]);
	}

	if (chdir(dirname) == 0) {
		return EXIT_SUCCESS;
	} else {
		printf("%s: failed to chdir to '%s'", args[0], dirname);
		return EXIT_FAILURE;
	}
}

int builtins_pwd(int argv, char **args) {
	if (argv != 0) {
		printf("%s: too many arguments\n", args[0]);
		return EXIT_FAILURE;
	}

	char cwd[512];
	if (!getcwd(cwd, sizeof cwd)) {
		printf("%s\n", cwd);
		return EXIT_SUCCESS;
	} else {
		printf("%s: could not get working directory\n", args[0]);
		return EXIT_FAILURE;
	}
}
