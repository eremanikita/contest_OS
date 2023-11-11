#include <stdio.h>
#include <stdlib.h>
#include "random_source.h"

enum
{
    A = 1103515245,
    C = 12345,
    M = 2147483648,
    SIZE_SOURCE = sizeof(RandomSource),
    SIZE_OPS = sizeof(RandomSourceOperations)
};

RandomSource *
linear_destroy(RandomSource *src)
{
    free(src->ops);
    free(src);
    return NULL;
}
double
linear_next(RandomSource *src)
{
    src->value = (src->value * A + C) % M;
    return (double) src->value / M;
}

RandomSource *
random_linear_factory(const char *params)
{
    unsigned long long seed;
    sscanf(params, "%llu", &seed);
    RandomSource *ptr = calloc(1, SIZE_SOURCE);
    RandomSourceOperations *ptr_ops = calloc(1, SIZE_OPS);
    ptr->value = seed;
    ptr->ops = ptr_ops;
    ptr->ops->destroy = linear_destroy;
    ptr->ops->next = linear_next;
    return ptr;
}
