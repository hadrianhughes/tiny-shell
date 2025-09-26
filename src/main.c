#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parse.h"
#include "tsh.h"

int main() {
  tsh_status_t status;

  do {
    char *line = readline("tsh ~> ");
    char **tokens = tokenize(line);

    status = run_cmd(tokens);
    add_history(line);

    free(tokens);
    free(line);
  } while (status == TSH_OK);

  return EXIT_SUCCESS;
}
