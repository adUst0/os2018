#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define ASSERT_LESS_THAN(errorMsg, x, y)          \
    if (x >= y) {                                 \
        fprintf(stderr, "Error: %s\n", errorMsg); \
        exit(1);                                  \
    }

#define BUFF_MAX_SIZE 1024
#define MAX_ARGS 64

typedef int (*Command)(char**, unsigned int);

/**
 * Read one line from STDIN
 *
 * @param[out]  buff  Buffer in which the line will be stored
 * @return      The size of the line, i.e. number of read bytes
 */
int readLine(char *buff) {
    int lineSize = 0;
    char c;

    while (read(0, &c, 1) > 0 && c != '\n') {
        buff[lineSize++] = c;

        ASSERT_LESS_THAN("Line length exceeds tha maximum size!", lineSize, BUFF_MAX_SIZE);
    }

    buff[lineSize] = '\0';

    return lineSize;
}

/**
 * Split line into arguments (words)
 * 
 * @param[in]   line
 * @param[out]  arguments   Array of char* where the arguments will be stored
 * @return      The number of arguments
 */
unsigned int splitLine(char *line, char *arguments[]) {
    unsigned int argumensCount = 0;
    char *word = strtok(line, " ");

    while (word != NULL) {
        arguments[argumensCount++] = word;
        word = strtok(NULL, " \t"); // split by space or tab

        ASSERT_LESS_THAN("Number of arguments exceeds the maximum size!", argumensCount, MAX_ARGS);
    }

    arguments[argumensCount] = NULL;

    return argumensCount;
}

int nthCharOfFile(char** args, unsigned int count) {
    if(count != 2) {
        printf("command <truncFile> expects two argument.\n");
        return -1;
    }
    char* file = args[0];
    char* n = args[1];
    int fd = open(file, O_RDONLY);
    long int nth = atol(n);
    char c;
    off_t offset;
    int whence;
    if(fd < 0) {
        perror("open");
        return -1;
    }
    if(!nth) {
        for(unsigned int i = 0; n[i]; ++i) {
            if(n[i] != '0') {
                printf("<nthCharOfFile> error: second argument <%s> is not a valid integer.\n", n);
                close(fd);
                return -1;
            }
        }
    }
    if(nth == 0) {
        printf("<nthCharOfFile> error:  second argument <0> is zero.\n");
        close(fd);
        return -1;
    }
    if(nth > 0) {
        offset = nth - 1;
        whence = SEEK_CUR;
    } else {
        offset = nth;
        whence = SEEK_END;
    }
    if(lseek(fd, offset, whence) < 0) {
        close(fd);
        return -1;
    }
    if(read(fd, &c, 1) != 1) {
        close(fd);
        return -1;
    }
    printf("<%ld> char of file <%s> is <%c>\n", nth, file, c);
    close(fd);
    return 0;
}

int truncFile(char** args, unsigned int count) {
    if(count != 1) {
        printf("command <truncFile> expects one argument.\n");
        return -1;
    }
    int fd = open(args[0], O_WRONLY | O_TRUNC);
    if(fd < 0) {
        perror("open");
        return -1;
    }
    printf("file <%s> has been truncated\n", args[0]);
    close(fd);
    return 0;
}

int printFile(char** args, unsigned int count) {
    if(count != 1) {
        printf("command <truncFile> expects one argument.\n");
        return -1;
    }
    char* file = args[0];
    int fd = open(file, O_RDONLY);
    const unsigned int buffSize = 4096;
    char buff[buffSize];
    if(fd < 0) {
        perror("open");
        return -1;
    }
    printf("file <%s> content:\n", file);
    while(1) {
        int readStatus = read(fd, buff, buffSize);
        if(!readStatus) {
            break;
        }
        if(readStatus > 0) {
            write(1, buff, readStatus);
        } else {
            return -1;
        }
    }
    close(fd);
    return 0;
}

int sizeOfFile(char** args, unsigned int count) {
    if(count != 1) {
        printf("command <sizeOfFile> expects one argument.\n");
        return -1;
    }
    struct stat statInfo;
    int error = stat(args[0], &statInfo);
    if(!error) {
        printf("file <%s> size: %ld\n", args[0], statInfo.st_size);
        return 0;
    }
    perror("stat");
    return -1;
}

int exec(char** args, unsigned int count) {
    pid_t pid = fork();
    int status;
    if(pid < 0) {
        perror("fork");
        return -1;
    }
    if(pid == 0) {
        if(execvp(args[0], args) < 0) {
            perror("execv");
            return -1;
        }
        return 0;
    } else {
        if(waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            return -1;
        }
        return status;
    }
}

int processInfo(char** args, unsigned int count) {
    if(!count) {
        printf("command <processInfo> have no arguments.\n");
        return -1;
    }
    printf("pid: %d ppid: %d\n", getpid(), getppid());
    return 0;
}

Command commandFromString(const char* const command) {
    const char* commands[] = {
        "nthCharOfFile",
        "truncFile",
        "printFile",
        "sizeOfFile",
        "exec",
        "processInfo"
    };
    Command cmdFunc[] = {
        nthCharOfFile,
        truncFile,
        printFile,
        sizeOfFile,
        exec,
        processInfo
    };
    const unsigned int length = (sizeof commands) / (sizeof(const char*));
    for(unsigned int i = 0; i < length; ++i) {
        if(!strcmp(commands[i], command)) {
            return cmdFunc[i];
        }
    }
    return NULL;
}

/**
 * Execute given command. Possible commands are described in the course repo @github 
 * 
 * @param[in]   arguments   Array of char* where the arguments are stored
 * @return      The exit status of the command
 */
int executeCommand(char *arguments[], unsigned int argumentsCount) {
    const char* command = arguments[0];
    char** cmdArgs = arguments + 1;
    unsigned int cmdArgsCount = argumentsCount - 1;
    Command cmd = commandFromString(command);
    if(cmd) {
        return cmd(cmdArgs, cmdArgsCount);
    }
    printf("<%s> is unknown command.\n", command);
    return 0;
}

int main() {
    char buff[BUFF_MAX_SIZE];
    char *arguments[MAX_ARGS + 1];

    while (1) {
        readLine(buff);
        printf("%s\n", buff);
        unsigned int argsCount = splitLine(buff, arguments);
        if(argsCount && !strcmp("exit", arguments[0])) {
            return EXIT_SUCCESS;
        }
        for (unsigned int i = 0; i < argsCount; i++) {
            printf("<%s>\n", arguments[i]);
        }
        int status = executeCommand(arguments, argsCount);
        printf("status: %d\n", status);
    }

    return EXIT_SUCCESS;
}
