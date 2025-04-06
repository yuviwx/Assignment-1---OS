#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    printf("enter goodbye.c\n");
    char buffer[32];
    int pid = fork();
    if(pid == 0){
        //printf("enter child process block\n");
        exit(0,"Goodbye World xv6");
    }
    else{
        //printf("enter parent process block\n");
        int child = wait(0,buffer);
        printf("child number %d left the following message: %s\n", child, buffer);
        exit(0,0);
    }
    
}
