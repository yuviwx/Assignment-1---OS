#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pids[4];
    int pid = forkn(4, pids);
    printf("after");
    if(pid == 0){
        for(int i = 0; i < 4; i++){
            printf("%d\n",pids[i]);
        }
    }
    printf("process number %d has exited", pid);
    exit(0,0);
}
