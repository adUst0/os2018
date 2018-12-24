#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    unsigned int fileSize = lseek(fd, 0, SEEK_END);
    printf("The size of \"%s\" is %u bytes\n", argv[1], fileSize);

    return EXIT_SUCCESS;
}