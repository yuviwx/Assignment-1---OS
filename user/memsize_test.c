#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main (int argc, char *argv[]) {
    printf("%d\n", memsize());
    char *a = malloc(20000);
    printf("%d\n", memsize());
    free(a);
    printf("%d\n", memsize());
    return 0;
}