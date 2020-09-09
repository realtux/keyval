#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashtable.h"
#include "repl.h"

char *read_command(void) {
    char letter;
    int input_len = 0;
    char *input = malloc(sizeof(char) * 1);
    input[0] = '\0';

    printf("keyval> ");

    // read characters one at a time until a newline
    while ((letter = fgetc(stdin)) != '\n') {
        ++input_len;
        input = realloc(input, sizeof(char) * input_len + 1);
        strcat(input, &letter);
    }

    return input;
}

char *read_token(char *input) {
    int input_len = strlen(input);
    int token_len = 0;
    char *token = malloc(sizeof(char) * 1);
    token[0] = '\0';

    int i = 0;

    // start by eating any space
    for (; i < input_len; ++i) {
        if (input[i] != ' ') break;
    }

    // read characters in one at a time until a space is encountered
    for (; i < input_len; ++i) {
        if (input[i] == ' ') break;

        ++token_len;
        token = realloc(token, sizeof(char) * token_len + 1);
        strncat(token, &input[i], 1);
    }

    // realign and resize memory to remove the token just found
    memmove(input, input + i, strlen(input) + 1 - i);
    input = realloc(input, sizeof(char) * strlen(input) + 1);

    return token;
}

void repl_init(void) {
    ht_t *ht = ht_create();

    // commands should be read in a loop, escapable by ^c
    for (;;) {
        // read a full line into input for processing
        char *input = read_command();

        // determine what op to handle (1 - get, 2 - set)
        int op = 0;

        // get a token (the op)
        char *token = read_token(input);

        if (strcmp(token, "get") == 0) {
            op = 1;
        } else if (strcmp(token, "set") == 0) {
            op = 2;
        }

        switch (op) {
            case 1: {
                char *key = read_token(input);
                printf("%s\n", ht_get(ht, key));
                free(key);
                break;
            }
            case 2: {
                char *key = read_token(input);
                char *value = read_token(input);
                ht_set(ht, key, value);
                free(key);
                free(value);
                break;
            }
            default:
                printf("invalid operation: %s\n", token);
        }

        free(token);
        free(input);
    }

    ht_destroy(ht);
}
