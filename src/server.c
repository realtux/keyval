#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

int sock_fd;

void *handle_op(void *arg) {
    int conn_fd = *((int *)arg);
    free(arg);

    int bytes_read;
    int len = 0;

    char c;
    char *buf = malloc(1 * sizeof(char));
    buf[0] = '\0';

    for (;;) {
        bytes_read = recv(conn_fd, &c, 1, 0);

        if (c == '\n' || bytes_read <= 0) {
            break;
        }

        ++len;
        buf = realloc(buf, (len + 1) * sizeof(char));

        buf[len-1] = c;
        buf[len] = '\0';
    }

    printf("%d: %s\n", conn_fd, buf);

    close(conn_fd);

    return NULL;
}

void *server_start(void) {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int bind_res;

    pthread_t thread;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd < 0) {
        printf("problem opening socket");
        return NULL;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(3424);

    bind_res = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (bind_res < 0) {
        printf("address binding failed");
        return NULL;
    }

    listen(sock_fd, 5);

    for (;;) {
        int *conn_fd = malloc(sizeof(int));

        *conn_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &client_addr_size);

        if (*conn_fd < 0) {
            printf("connection accept failed");
            free(conn_fd);
            continue;
        }

        pthread_create(&thread, NULL, handle_op, conn_fd);
        pthread_join(thread, NULL);
    }

    return NULL;
}
