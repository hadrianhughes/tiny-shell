#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "read.h"

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

int main() {
  char *line = read_line();
  char **tokens = split_tokens(line);

  run_program(tokens);

  free(tokens);
  free(line);

  return EXIT_SUCCESS;
}
