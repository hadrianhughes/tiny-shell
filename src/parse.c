#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

char **tokenize(char *line) {
  size_t buf_size = TOKEN_BUF_SIZE;
  size_t num_tokens = 0;

  char **tokens = (char **) malloc(sizeof(char *) * buf_size);
  if (!tokens) {
    perror("tsh: failed to allocate tokens array");
    exit(EXIT_FAILURE);
  }

  char *token_start = NULL;

  bool in_quotes = false;

  for (char *p = line;; p++) {
    char c = *p;

    if (c == '\0') {
      if (token_start) {
        tokens[num_tokens++] = token_start;
        token_start = NULL;
      }

      break;
    }

    if (c == '"') {
      if (in_quotes) {
        *p = '\0';
        tokens[num_tokens++] = token_start;
        token_start = NULL;
      }

      in_quotes = !in_quotes;

      continue;
    }

    if (c == ' ' || c == '\n' || c == '\r') {
      if (token_start) {
        *p = '\0';
        tokens[num_tokens++] = token_start;
        token_start = NULL;
      }
    } else if (!token_start) {
      token_start = p;
    }

    if (num_tokens >= buf_size) {
      buf_size += TOKEN_BUF_SIZE;
      tokens = (char **) realloc(tokens, sizeof(char *) * buf_size);
    }
  }

  return tokens;
}
