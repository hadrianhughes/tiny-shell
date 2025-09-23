#ifndef TSH_H_
#define TSH_H_

typedef int tsh_status_t;
#define TSH_OK 0
#define TSH_EXIT 1
#define TSH_ERROR -1

tsh_status_t run_cmd(char **args);

#endif
