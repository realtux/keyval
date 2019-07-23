#include <stdio.h>
#include <pthread.h>

#include "config.h"
#include "repl.h"
#include "server.h"

extern keyval_config config;

int main(int argc, char **argv) {
    parse_opts(argc, argv);

    // check for and start repl if requested
    if (config.is_repl) {
        repl_init();
        return 0;
    }

    // start server listener
    pthread_t thread;
    pthread_create(&thread, NULL, server_start, NULL);
    pthread_join(thread, NULL);

    return 0;
}
