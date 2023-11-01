#ifndef __rand_source_H__
#define __rand_source_H__

typedef struct _RandomSourceOperations RandomSourceOperations;

typedef struct
{
    unsigned long long value;
    RandomSourceOperations *ops;
} RandomSource;

typedef struct _RandomSourceOperations
{
    RandomSource * (*destroy) (RandomSource *);
    double (*next) (RandomSource *);
} RandomSourceOperations;

#endif