#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUF_SIZE 1024
#define TOKEN_BUF_SIZE 64
#define TOKEN_DELIM_CHARS " \t\n\r\a"

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

char **split_tokens(char *line) {
  size_t buf_size = TOKEN_BUF_SIZE;
  size_t num_tokens = 0;

  char **tokens = malloc(sizeof(char*) * buf_size);
  if (!tokens) {
    perror("tsh: failed to allocate tokens array");
    exit(EXIT_FAILURE);
  }

  char *current_token = strtok(line, " \t\r\n\a");

  while (current_token != NULL) {
    tokens[num_tokens++] = current_token;

    if (num_tokens >= buf_size) {
      buf_size += TOKEN_BUF_SIZE;
      tokens = realloc(tokens, sizeof(char*) * buf_size);

      if (!tokens) {
        perror("tsh: failed to reallocate tokens array");
        exit(EXIT_FAILURE);
      }
    }

    current_token = strtok(NULL, TOKEN_DELIM_CHARS);
  }

  tokens[num_tokens] = NULL;

  return tokens;
}

int main() {
  char *line = read_line();
  char **tokens = split_tokens(line);

  size_t position = 0;
  while (tokens[position] != NULL) {
    printf("%s\n", tokens[position++]);
  }

  free(line);
  free(tokens);

  return EXIT_SUCCESS;
}
