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
    // then inverse the file and print it to standard output
    struct stat metadata;
    int fd = open("titi.dat", O_RDWR, 0666);
    stat("titi.dat", &metadata);
    int *tab = (int *)mmap(NULL, metadata.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // reverse the array tab
    int i, j;
    for (i = 0, j = 9; i < j; i++, j--)
    {
        int tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }
    // print the file
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", tab[i]);
        fflush(stdout);
    }
    munmap(tab, metadata.st_size);
    close(fd);
    return 0;
}