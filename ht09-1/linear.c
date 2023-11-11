#include "random_source.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

RandomSource *
linear_destroy(RandomSource *src)
{
    printf("dfdf");
//    free(src->ops);
//    free(src);
    return NULL;
}

double
linear_next(RandomSource *src)
{
    unsigned long long A = 1103515245;
    unsigned long long C = 12345;
    unsigned long long M = 1ull << 31;
    src->value = (A * src->value + C) % M;
    return src->value / ((double) M);
}

RandomSource *
random_linear_factory(const char *seed)
{
    RandomSource *rr = calloc(1, sizeof(RandomSource));
    sscanf(seed, "%llu", &rr->value);
    rr->ops = calloc(1, sizeof(rr->ops));
    rr->ops->destroy = linear_destroy;
    rr->ops->next = linear_next;
    sleep(5);
    printf("%d - lin dest\n", rr->ops->destroy);
    printf("%d - lin next\n", rr->ops->next);
    return rr;
}
