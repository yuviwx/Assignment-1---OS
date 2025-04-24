#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int n;
    int statuses[64];
    
    // Call waitall with no child processes
    printf("Testing waitall with no children:\n");
    int result = waitall(&n, statuses);
    
    if(result == 0 && n == 0)
        printf("  Passed: waitall correctly returned with n=0\n");
    else
        printf("  Failed: waitall should set n=0 but got n=%d, result=%d\n", n, result);
    
    exit(0, 0);
}