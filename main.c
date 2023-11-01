#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include "random_source.h"

enum
{
    FIRST_PARAM = 1,
    SECOND_PARAM = 2,
    THIRD_PARAM = 3
};

int
main(int argc, char *argv[])
{
    void *handle = dlopen(NULL, RTLD_LAZY);
    RandomSource * (* ptr_func) (const char *params) = NULL;
    RandomSource *ptr_value = NULL;
    int n;
    sscanf(argv[SECOND_PARAM], "%d", &n);
    if (!strcmp(argv[FIRST_PARAM], "linear")) {
        ptr_func = dlsym(handle, "random_linear_factory");
        ptr_value = ptr_func(argv[THIRD_PARAM]);
    } else {
        ptr_func = dlsym(handle, "random_random_factory");
        ptr_value = ptr_func(NULL);
    }

    for (int i = 0; i < n; i++) {
        printf("%.10g\n", ptr_value->ops->next(ptr_value));
    }

    ptr_value->ops->destroy(ptr_value);
    dlclose(handle);
    return 0;
}