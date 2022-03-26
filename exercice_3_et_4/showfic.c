#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    // mmap() on titi.dat
    struct stat metadata;
    int fd = open("titi.dat", O_RDWR, 0666);
    stat("titi.dat", &metadata);
    int *tab = (int *)mmap(NULL, metadata.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    int i;
    scanf("%d", &i);
    // if i == 99, exit the program
    if (i == 99)
        exit(0);
    else // else print the whole tab in mmap segment
    {
        for (i = 0; i < 10; i++)
            printf("%d\n", tab[i]);
        fflush(stdout);
    }
    return 0;
}
