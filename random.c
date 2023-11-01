#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <limits.h>
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
random_destroy(RandomSource *src)
{
    close(src->value);
    free(src->ops);
    free(src);
    return NULL;
}

double
random_next(RandomSource *src)
{
    unsigned long long tmp;
    read(src->value, &tmp, sizeof(tmp));
    return (double) (tmp % ULLONG_MAX) / ULLONG_MAX;
}

RandomSource *
random_random_factory(const char *params)
{
    int rand_data = open("/dev/urandom", O_RDONLY);
    RandomSource *ptr = calloc(1, SIZE_SOURCE);
    RandomSourceOperations *ptr_ops = calloc(1, SIZE_OPS);
    ptr->value = rand_data;
    ptr->ops = ptr_ops;
    ptr->ops->destroy = random_destroy;
    ptr->ops->next = random_next;
    return ptr;
}
