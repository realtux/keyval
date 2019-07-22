#include <stdio.h>
#include <pthread.h>

#include "server.h"

int main(void) {
    // start server listener
    pthread_t thread;
    pthread_create(&thread, NULL, server_start, NULL);
    pthread_join(thread, NULL);

    return 0;
}
