#include <stdio.h>
#include <stdlib.h>
#include "random_source.h"
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

RandomSource *
destroy(RandomSource *src)
{
    free(src->ops);
    free(src);
    return NULL;
}

double
next(RandomSource *src)
{
    unsigned long long val;
    read(src->fd, &val, 8);
    src->val = (val % ULLONG_MAX) / (double) ULLONG_MAX;
    return src->val;
}

RandomSource *
random_random_factory(void)
{
    RandomSource *rr = calloc(sizeof(RandomSource), 1);
    int fd = open("/dev/urandom", O_RDONLY);
    rr->fd = fd;
    read(fd, &rr->value, 8);
    rr->ops = calloc(1, sizeof(rr->ops));
    rr->ops->destroy = destroy;
    rr->ops->next = next;
    return rr;
}
