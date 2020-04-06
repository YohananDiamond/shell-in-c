#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "token.h"

#include "shell.h"

int run_command(char **args) {
    int argv = tokens_len(args);

    if (argv == 0) {
        return 0;
    }
    else if (!strcmp(args[0], "exit")) {
        return builtin_exit(argv, args);
    }
    else if (!strcmp(args[0], "cd")) {
        return builtin_cd(argv, args);
    }
    else {
        printf("unknown command: %s\n", args[0]);
        return EXIT_FAILURE;
    }
}

int builtin_exit(int argv, char **args) {
    if (argv == 0)
        exit(EXIT_SUCCESS);

    if (argv == 1) {
        int code = (int)strtol(args[1], NULL, 10);
        exit(code);
    } else {
        printf("exit: invalid amount of arguments\n");
        return EXIT_FAILURE;
    }
}

int builtin_cd(int argv, char **args) {
    if (argv == 0) {
        chdir(getenv("HOME"));
        return EXIT_SUCCESS; /* Not sure on how to do error handling on this yet */
    }

    if (argv == 1) {
        chdir(args[1]);
        return EXIT_SUCCESS;
    } else {
        printf("cd: invalid amount of arguments");
        return EXIT_FAILURE;
    }
}

/* int execute_command(char **args) { */
/*     pid_t pid, wpid; */
/*     int status; */

/*     pid = fork(); */
/*     if (pid == 0) { */
/*         /1* The process is a child process *1/ */
/*         if (execvp(args[0], args) == -1) */
/*             perror("shell"); */
/*         exit(EXIT_FAILURE); */
/*     } else if (pid < 0) { */
/*         /1* The forking failed *1/ */
/*         perror("shell"); */
/*     } else { */
/*         /1* The process is a parent process *1/ */
/*         do { */
/*             wpid = waitpid(pid, &status, WUNTRACED); */
/*         } while (!WIFEXITED(status) && !WIFSIGNALED(status)); */
/*     } */

/*     return 1; */
/* } */