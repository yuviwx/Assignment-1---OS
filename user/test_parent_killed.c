#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int pids[4];
    int pid = getpid();
    
    // Create another process to kill this one
    if(fork() == 0) {
        // Child sleeps to give parent time to start waitall
        sleep(10);
        printf("Killing parent process %d\n", pid);
        kill(pid);
        exit(0, 0);
    }
    
    // Create 4 child processes that will sleep
    int result = forkn(4, pids);
    if(result == 0) {
        printf("Parent waiting for children...\n");
        int n;
        int statuses[4];
        // This should be interrupted when the parent is killed
        int wait_result = waitall(&n, statuses);
        printf("waitall returned: %d\n", wait_result);
    }
    else if(result > 0) {
        // Child sleeps for a while
        sleep(100);
        exit(0, 0);
    }
    
    exit(0, 0);
}