#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pids[4];
    int result = forkn(4, pids);
    int n; int statuses[4];

    // This will run in the parent only
    if(result == 0){
        printf("Parent process: created 4 children:\n");
        for(int i = 0; i < 4; i++){
            printf("Child PID: %d\n", pids[i]);
        }

        // wait for all children
        waitall(&n, statuses);
        if(n != 4) exit(-1,"Error: not all children exited but waitall finished");

        // sum up
        int output = 0;
        for(int i = 0; i < 4; i++){
            output += statuses[i];
        }

        printf("Parent calculation: %d\n", output);
    }
    else if(result == -1){
        printf("forkn failed\n");
        exit(-1,"");
    }
    // else it's a child so calculate
    else{
        int num = 1 << 14; // 2^16/4
        int startNum = (result - 1) * num;
        int endNum = result * num;
        int output = 0;
        for(int i = startNum; i < endNum; i++){
            output += i;
        }
        printf("%d",output);
        exit(output,0);
    }

    exit(0, 0);
}
