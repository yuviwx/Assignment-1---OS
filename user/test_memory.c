#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    // Allocate a small array
    int *array = malloc(4096);
    if(!array) {
        printf("Failed to allocate memory\n");
        exit(-1, 0);
    }
    
    printf("Parent: before fork, memory size = %d\n", memsize());
    
    int pids[4];
    int result = forkn(4, pids);
    
    if(result == 0) {
        printf("Parent: after fork, memory size = %d\n", memsize());
        
        int n;
        int statuses[4];
        waitall(&n, statuses);
        
        printf("Parent: after waitall, memory size = %d\n", memsize());
        free(array);
        printf("Parent: after free, memory size = %d\n", memsize());
    }
    else if(result > 0) {
        // Child just checks its memory size
        printf("Child %d: memory size = %d\n", result, memsize());
        exit(0, 0);
    }
    
    exit(0, 0);
}