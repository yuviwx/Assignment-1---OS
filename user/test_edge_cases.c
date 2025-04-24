#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int pids[17]; // Intentionally larger than max allowed
    
    // Test with invalid n values
    printf("Testing with n=0 (should fail):\n");
    int result = forkn(0, pids);
    if(result == -1)
        printf("  Passed: forkn correctly rejected n=0\n");
    else
        printf("  Failed: forkn should reject n=0 but returned %d\n", result);
    
    printf("Testing with n=-1 (should fail):\n");
    result = forkn(-1, pids);
    if(result == -1)
        printf("  Passed: forkn correctly rejected n=-1\n");
    else
        printf("  Failed: forkn should reject n=-1 but returned %d\n", result);
    
    printf("Testing with n=17 (should fail):\n");
    result = forkn(17, pids);
    if(result == -1)
        printf("  Passed: forkn correctly rejected n=17\n");
    else
        printf("  Failed: forkn should reject n=17 but returned %d\n", result);
    
    // Test with valid n but at the boundary
    printf("Testing with n=16 (should succeed):\n");
    result = forkn(16, pids);
    if(result == 0) {
        printf("  Passed: Parent process created 16 children\n");
        int n;
        int statuses[16];
        waitall(&n, statuses);
        printf("  Children waited: %d\n", n);
    }
    else if(result > 0 && result <= 16) {
        printf("  Child process %d exiting\n", result);
        exit(0, 0);
    }
    else {
        printf("  Failed: forkn returned unexpected value %d\n", result);
    }
    
    exit(0, 0);
}