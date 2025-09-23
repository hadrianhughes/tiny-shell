#include <stdio.h>
#include <stdlib.h>

#include "read.h"

int main() {
  char *line = read_line();
  char **tokens = split_tokens(line);

  size_t position = 0;
  while (tokens[position] != NULL) {
    printf("%s\n", tokens[position++]);
  }

  free(tokens);
  free(line);

  return EXIT_SUCCESS;
}
