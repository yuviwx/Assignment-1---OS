#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int pids[4];
    int result = forkn(4, pids);

    // This will run in the parent only
    if(result == 0){
        printf("Parent process: created 4 children:\n");
        for(int i = 0; i < 4; i++){
            printf("Child PID: %d\n", pids[i]);
        }
        int n;
        int statuses[5];
        waitall(&n, statuses);
        printf("the number of children: %d\n", n);
        for(int i=0; i<n; i++) {
            printf("child number %d exit status is: %d\n", i, statuses[i]);
        }
        printf("Parent exiting\n");
    }

    exit(0, 0);
}
