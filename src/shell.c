#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "token.h"

#include "shell.h"

int builtin_exit(int argv, char **args);
int builtin_cd(int argv, char **args);
int builtin_pwd(int argv, char **args);

int run_args(char **args) {
    int argv = tokens_len(args);

    if (argv == 0) {
        return 0;
    } else if (!strcmp(args[0], "exit")) {
        return builtin_exit(argv, args);
    }
    else if (!strcmp(args[0], "cd")) {
        return builtin_cd(argv, args);
    } else if (!strcmp(args[0], "pwd")) {
        return builtin_pwd(argv, args);
    } else {
        return fork_and_execute(args);
    }
}

int builtin_exit(int argv, char **args) {
    if (argv == 1) {
        exit(EXIT_SUCCESS);
    } else if (argv == 2) {
        int code = (int)strtol(args[1], NULL, 10);
        exit(code);
    } else {
        printf("exit: invalid amount of arguments\n");
        return EXIT_FAILURE;
    }
}

int builtin_cd(int argv, char **args) {
    if (argv == 1) {
        chdir(getenv("HOME"));
        return EXIT_SUCCESS; /* Not sure on how to do error handling on this yet */
    } else if (argv == 2) {
        chdir(args[1]);
        return EXIT_SUCCESS;
    } else {
        printf("cd: invalid amount of arguments\n");
        return EXIT_FAILURE;
    }
}

int builtin_pwd(int argv, char **args) {
    if (argv == 1) {
        char cwd[256];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
            return 0;
        } else {
            printf("pwd: could not get current working dir\n");
            return 1;
        }
    } else {
        printf("pwd: too many arguments\n");
        return 0;
    }
}

int fork_and_execute(char **args) {
    /* Pretty much copied this one from the tutorial :P */
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* The process is a child process */
        if (execvp(args[0], args) == -1)
            perror("shell");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* The forking failed */
        perror("shell");
    } else {
        /* The process is a parent process */
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
