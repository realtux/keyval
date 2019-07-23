#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int is_repl;
    int is_server;
} keyval_config;

void parse_opts(int, char**);

#endif
