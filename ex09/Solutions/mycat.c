#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE (1024U)

int printError(const char* message) 
{
    return write(2, message, strlen(message));
}

int main(int argc, char *argv[]) 
{
    char buff[BUFF_SIZE];
    int bytesCount;

    if (argc == 1) 
    {
        bytesCount = read(0, buff, BUFF_SIZE);
        while (bytesCount > 0) 
        {
            write(1, buff, bytesCount);
            bytesCount = read(0, buff, BUFF_SIZE);
        }

        exit(0);
    }

    for (int i = 1; i < argc; i++) 
    {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) 
        {
            perror(argv[i]);
            exit(1);
        }

        bytesCount = read(fd, buff, BUFF_SIZE);
        while (bytesCount > 0) 
        {
            write(1, buff, bytesCount);
            bytesCount = read(fd, buff, BUFF_SIZE);
        }
    }

    return 0;
}