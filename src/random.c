#include <random.h>
#include <stdlib.h>

double rand_double(void) {
    return (double) rand() / (double) RAND_MAX;
}
