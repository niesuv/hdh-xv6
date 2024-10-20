
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char *path, char *name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, O_RDONLY)) < 0)
    {
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:
        if (strcmp(path + strlen(path) - strlen(name), name) == 0)
        {
            printf("%s\n", path);
        }
        break;

    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0)
            {
                find(buf, name);
            }
        }
        break;
    }
    close(fd);
}

void main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("find: You must enter destination and filename to search\n");
    }
    else
    if (argc < 3)
    {
        printf("find: You must enter filename to search\n");
    }
    else
    {
        find(argv[1], argv[2]);
    }
    exit(0);
}
