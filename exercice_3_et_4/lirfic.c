#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "inific.h"

#define BUFFER_SIZE 1024

int copy_file(int f1, int f2)
{
    int nb_bytes_read = 0;
    char buffer[1024];
    int nb_bytes_written = 0;
    while ((nb_bytes_read = read(f1, buffer, 1024)) > 0)
    {
        nb_bytes_written = write(f2, buffer, nb_bytes_read);
        if (nb_bytes_written != nb_bytes_read)
        {
            printf("error while writing\n");
            return -1;
        }
    }
    return nb_bytes_written;
}

int main(int argc, char *argv[])
{
    // read file passed as argument 1 and print it to standard output
    int tab[10];
    int fd = open(argv[1], O_RDONLY);
    read(fd, tab, 10 * sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", tab[i]);
    }
    close(fd);
    return 0;
}