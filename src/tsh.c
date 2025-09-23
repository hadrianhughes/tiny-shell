#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tsh.h"

#define NUM_BUILTINS 2

void tsh_cd(char **args);
void tsh_exit(char **args);

char *tsh_cmds[] = {
  "cd",
  "exit"
};

void (*tsh_funcs[]) (char **) = {
  &tsh_cd,
  &tsh_exit
};

void tsh_cd(char **args) {
  if (args[1] == NULL) {
    perror("tsh: expected argument to command: \"cd\"");
    return;
  }

  if (chdir(args[1]) != 0) {
    perror("tsh: failed to change directory");
  }
}

void tsh_exit(char **args) {
  return;
}

void run_program(char **args) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("tsh: failed to fork process");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    // child process
    if (execvp(args[0], args) == -1) {
      perror("tsh: failed to execute command");
    }

    exit(EXIT_FAILURE);
  } else {
    // parent process
    int status;
    pid_t wpid;

    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(wpid) && !WIFSIGNALED(wpid));
  }
}

void run_cmd(char **args) {
  if (args[0] == NULL) {
    return;
  }

  for (int i = 0;i < NUM_BUILTINS;i++) {
    if (strcmp(args[0], tsh_cmds[i]) == 0) {
      return (*tsh_funcs)(args);
    }
  }

  run_program(args);
}
