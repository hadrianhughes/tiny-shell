#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "read.h"
#include "tsh.h"

int main() {
  char *line = read_line();
  char **tokens = split_tokens(line);

  run_cmd(tokens);

  free(tokens);
  free(line);

  return EXIT_SUCCESS;
}
