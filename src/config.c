#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"

keyval_config config;

void menu(void) {
    printf(
        "usage: keyval [args]\n\n"
        "args:\n"
        "  -s   start server in foreground\n"
        "  -c   start interactive client\n"
        "       requires running server to use\n"
    );
}

void parse_opts(int argc, char **argv) {
    int i;

    config.is_repl = 0;
    config.is_server = 0;

    if (argc == 1) {
        menu();
        exit(0);
    }

    for (i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-c") == 0) {
            config.is_repl = 1;
        } else if (strcmp(argv[i], "-s") == 0) {
            config.is_server = 1;
        }
    }
}
