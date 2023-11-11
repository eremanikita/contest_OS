#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include "random_source.h"

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        exit(1);
    }
    int number;
    if (!strcmp(argv[1], "linear")) {
        sscanf(argv[2], "%d", &number);
        void *handle;
        char *error;
        RandomSource *(*linear_factory)(const char *);
        handle = dlopen(NULL, RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "Linear handle error\n");
            exit(1);
        }
        linear_factory = dlsym(handle, "random_linear_factory");

        if ((error = dlerror()) != NULL) {
            fprintf(stderr, "%s\n", error);
            exit(1);
        }
        RandomSource *rr = linear_factory(argv[3]);
        for (int i = 0; i < number; i++) {
            printf("%.10g\n", rr->ops->next(rr));
        }
        printf("%d", rr->ops->next);
        //rr->ops->destroy(rr);
        dlclose(handle);
    } else if (!strcmp(argv[1], "random")) {
        sscanf(argv[2], "%d", &number);
        void *handle;
        char *error;
        RandomSource *(*random_factory)(void);
        handle = dlopen(NULL, RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "Random handle error\n");
            exit(1);
        }
        random_factory = dlsym(handle, "random_random_factory");
        if ((error = dlerror()) != NULL) {
            fprintf(stderr, "%s\n", error);
            exit(1);
        }
        RandomSource *rr = random_factory();
        for (int i = 0; i < number; i++) {
            printf("%.10g\n", rr->ops->next(rr));
        }
        rr->ops->destroy(rr);
        dlclose(handle);
    }
    return 0;
}
