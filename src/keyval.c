#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "benchmark.h"

int main(void) {
    hashtable_benchmark(200000);
    return 0;
}
