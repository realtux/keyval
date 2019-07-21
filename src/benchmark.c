#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hashmap.h"

void ht_benchmark(int interations) {
    clock_t start, end;
    double set_time;
    double get_time;

    ht_t *ht = ht_create();

    char temp[16];

    // set
    start = clock();
    for (int i = 0; i < interations; ++i) {
        sprintf(temp, "test%d", i);
        ht_set(ht, temp, temp);
    }
    end = clock();
    set_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    // get
    start = clock();
    for (int i = 0; i < interations; ++i) {
        sprintf(temp, "test%d", i);
    }
    end = clock();
    get_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("setting %d took: %fs, %fms\n", interations, set_time, set_time * 1000);
    printf("getting %d took: %fs, %fms\n", interations, get_time, get_time * 1000);

    ht_destroy(ht);
}
