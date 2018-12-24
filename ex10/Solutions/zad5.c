#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        printf("Incorrect usage.\n");
        return EXIT_FAILURE;
    }

    if (fork() == 0) {
        if (execvp(argv[1], argv + 1) == -1) {
            return EXIT_FAILURE;
        }
    }
    else {
        printf("Command started successfully!\n");
    }

    return EXIT_SUCCESS;
}