#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tsh.h"

#define NUM_BUILTINS 2

tsh_status_t tsh_cd(char **args);
tsh_status_t tsh_exit(char **args);

char *tsh_cmds[] = {
  "cd",
  "exit"
};

tsh_status_t (*tsh_funcs[]) (char **) = {
  &tsh_cd,
  &tsh_exit
};

tsh_status_t tsh_cd(char **args) {
  if (args[1] == NULL) {
    perror("tsh: expected argument to command: \"cd\"");
    return TSH_OK;
  }

  if (chdir(args[1]) != 0) {
    perror("tsh: failed to change directory");
  }

  return TSH_OK;
}

tsh_status_t tsh_exit(char **args) {
  (void)args;

  return TSH_EXIT;
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
      if (errno == ENOENT) {
        printf("tsh: command not recognised: %s\n", args[0]);
      } else {
        perror("tsh: failed to execute command");
      }
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

tsh_status_t run_cmd(char **args) {
  if (args[0] == NULL) {
    return TSH_OK;
  }

  for (int i = 0;i < NUM_BUILTINS;i++) {
    if (strcmp(args[0], tsh_cmds[i]) == 0) {
      return (*tsh_funcs[i])(args);
    }
  }

  run_program(args);

  return TSH_OK;
}
