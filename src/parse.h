#ifndef PARSE_H_
#define PARSE_H_

#define LINE_BUF_SIZE 1024
#define TOKEN_BUF_SIZE 64
#define TOKEN_DELIM_CHARS " \t\n\r\a"

char **tokenize(char *line);

#endif
