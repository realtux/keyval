#include <stdio.h>

#include "benchmark.h"
#include "hashtable.h"

int main(void) {
    ht_t *ht = ht_create();

    ht_set(ht, "name", "brian");
    ht_set(ht, "age", "34");

    printf("%s is %s\n", ht_get(ht, "name"), ht_get(ht, "age"));

    ht_benchmark(200000);

    return 0;
}
