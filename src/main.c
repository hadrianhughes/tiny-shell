#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_BUF_SIZE 1024

char *read_line(void) {
  size_t buf_size = LINE_BUF_SIZE;
  char *buffer = NULL;

  if (getline(&buffer, &buf_size, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);
    } else {
      perror("tsh: failed to read line from stdin");
      exit(EXIT_FAILURE);
    }
  }

  return buffer;
}

int main(int argc, char **argv) {

  char *line = read_line();
  printf("%s\n", line);
  free(line);

  return EXIT_SUCCESS;
}
