#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void toRead(int *p) {
    close(0);
    dup(p[0]);
    close(p[0]);
    close(p[1]);
}


void toWrite(int *p) {
    close(1);
    dup(p[1]);
    close(p[0]);
    close(p[1]);
}


void recursive() {
    int p[2];
    int first;
    if (read(0, &first, sizeof(first))) {
        printf("prime %d\n", first);
    }
    pipe(p);
    if (fork() > 0) {
        toRead(p);
        recursive();
    }
    else {
        int byte;
        toWrite(p);
        while (read(0, &byte, sizeof(byte))) {
            if (byte % first != 0)
                write(1, &byte, sizeof(byte));
        }
    }

}

int
main(int argc, char** argv) {
    //int n = 280;
    if (argc > 1) {
        //n = atoi(argv[1]);
    }
    int p[2];
    pipe(p);
    if (fork() > 0) {
        toRead(p);
        recursive();
    }
    else {
        toWrite(p);
        for (int i = 2; i <= 285; i++) {
            write(1, &i, sizeof(i));
        }
    }
    exit(0);
}