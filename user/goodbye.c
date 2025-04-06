#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char buffer[32];
    int pid = fork();
    if(pid == 0){
        exit(0,"Goodbye World xv6");
    }
    else{
        int child = wait(0,buffer);
        printf("child number %d left the following message: %s\n", child, buffer);
        exit(0,0);
    }
    
}
