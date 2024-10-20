#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(int argc, char **argv)
{
    int p[2];
    pipe(p);
    if (fork() > 0)
    {   
        //send ping
        write(p[1], (void*)'a', 1);
        wait(0);
        char byte[1];
        if (read(p[0], byte, 1) > 0)
        {
            fprintf(0, "%d: received pong\n", getpid());
            close(p[0]);
            close(p[1]);
        }
        
    exit(0);
    }
    else
    {
        char byte[1];
        if (read(p[0], byte, 1) > 0)
        {
            fprintf(0, "%d: received ping\n", getpid());
            write(p[1], byte, 1);
            close(p[0]);
            close(p[1]);
        }
    }

}
