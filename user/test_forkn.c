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

        // wait for all children
        for(int i = 0; i < 4; i++) {
            wait(0, 0);
        }

        printf("Parent exiting\n");
    }

    exit(0, 0);
}
