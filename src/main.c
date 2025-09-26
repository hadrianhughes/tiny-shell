#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "read.h"
#include "tsh.h"

int main() {
  tsh_status_t status;

  do {
    char *line = readline("tsh ~> ");

    add_history(line);

    char **tokens = tokenize(line);
    status = run_cmd(tokens);

    free(tokens);
    free(line);
  } while (status == TSH_OK);

  return EXIT_SUCCESS;
}
