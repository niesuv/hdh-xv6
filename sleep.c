#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char** argv) {
    if (argc < 2) {
        printf("sleep: You must pass a period of time you want to sleep!\n");
    }
    else {
        sleep(atoi(argv[1]));
    }
    exit(0);

}

