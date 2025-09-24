#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "read.h"
#include "tsh.h"

int main() {
  tsh_status_t status;

  do {
    print_prompt();
    char *line = read_line();
    char **tokens = tokenize(line);

    status = run_cmd(tokens);

    free(tokens);
    free(line);
  } while (status == TSH_OK);

  return EXIT_SUCCESS;
}
