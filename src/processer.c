#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "main.h"

/* internal functions */
int processer_run_program(char *parent_name, Token *args);

int processer_process_args(char *parent_name, int argv, Token *args) {
	if (argv == 0) return 0;

	if (strcmp(args[0], "exit") == 0)
		return builtins_exit(argv, args);
	if (strcmp(args[0], "chdir") == 0)
		return builtins_chdir(argv, args);
	if (strcmp(args[0], "cd") == 0)
		return builtins_chdir(argv, args);
	if (strcmp(args[0], "pwd") == 0)
		return builtins_pwd(argv, args);

	return processer_run_program(parent_name, args);
}

int processer_run_program(char *parent_name, Token *args) {
	pid_t fork_pid, wait_pid;
	int exit_status;

	/* make the fork */
	fork_pid = fork();

	/* child process */
	if (fork_pid == 0) {
		if (execvp(args[0], args) == -1)
			perror(parent_name);
		exit(EXIT_FAILURE);

	/* forking failed */
	} else if (fork_pid < 0) {
		perror(parent_name);
		return EXIT_FAILURE;

	/* parent process */
	} else {
		do {
			wait_pid = waitpid(fork_pid, &exit_status, WUNTRACED);
		} while (!WIFEXITED(exit_status) && !WIFSIGNALED(exit_status));
	}

	return exit_status;
}
