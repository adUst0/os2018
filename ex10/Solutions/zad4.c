#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (fork() == 0) {
        execl("/usr/bin/wc", "wc", "-c", argv[0], 0);
    }
    else {
        wait(NULL);
    }

    if (fork() == 0) {
        execlp("wc", "wc", "-c", argv[0], 0);
    }
    else {
        wait(NULL);
    }

    char *command[] = {"/usr/bin/wc", "wc",  "-c", argv[0], NULL};

    if (fork() == 0) {
        execv(command[0], command + 1);
    }
    else {
        wait(NULL);
    }


    if (fork() == 0) {
        execvp(command[1], command + 1);
    }
    else {
        wait(NULL);
    }
    
    printf("Exit...\n");

    return EXIT_SUCCESS;
}