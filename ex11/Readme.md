# Упражнение 11

### Задача

Ще направим прост команден интерпретатор, който поддържа няколко команди, които ще дефинираме след малко. 

Разгледайте приложения код. Имплементирайте функцията `executeCommand(char *arguments[])`, която приема като аргумент команда - масив от низове и изпълнява командата. 

**За всички I/O операции използвайте системни примитиви.** Обърнете внимание на функцията *readLine*, тъй като се очаква да може да я имплементирате.

**Командите, които поддържаме са:** 
1. **Команди свързани с файлове**
	 - `nthCharOfFile fileName n` - отпечатва n-тия символ от файла (ако съществува и има поне n символа)
	- `truncFile fileName` - изтрива съдържанието на файла (ако съществува)
	 - `printFile fileName` - отпечатва съдържанието на файла (ако съществува)
	 - `sizeOfFile fileName` - отпечатва размера на файла (ако съществува)

        При грешка, функцията връща -1. При успех: 0.

2. **Команди свързани с процеси**
	 - `exec cmd [arg1 arg2 ... ]` - изпълнява командата.

	При грешка в стартирането на процеса - функцията трябва да върне -1. В противен случай, функцията изчаква процеса да завърши и връща кода му на завършване.

	 - `processInfo` - отпечатва PID на текущия и на родителския процес

**Имплементация**:

```c
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define ASSERT_LESS_THAN(errorMsg, x, y)          \
    if (x >= y) {                                 \
        fprintf(stderr, "Error: %s\n", errorMsg); \
        exit(1);                                  \
    }

#define BUFF_MAX_SIZE 1024
#define MAX_ARGS 64

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
int splitLine(char *line, char *arguments[]) {
    int argumensCount = 0;
    char *word = strtok(line, " ");

    while (word != NULL) {
        arguments[argumensCount++] = word;
        word = strtok(NULL, " \t"); // split by space or tab

        ASSERT_LESS_THAN("Number of arguments exceeds the maximum size!", argumensCount, MAX_ARGS);
    }

    arguments[argumensCount] = NULL;

    return argumensCount;
}

/**
 * Execute given command. Possible commands are described in the course repo @github 
 * 
 * @param[in]   arguments   Array of char* where the arguments are stored
 * @return      The exit status of the command
 */
int executeCommand(char *arguments[]) {
    // TODO
}

int main() {
    char buff[BUFF_MAX_SIZE];
    char *arguments[MAX_ARGS + 1];

    while (1) {
        int lineSize = readLine(buff);
        printf("%s\n", buff);
        int argsCount = splitLine(buff, arguments);
        for (int i = 0; i < argsCount; i++) {
            printf("<%s>\n", arguments[i]);
        }
        int status = executeCommand(arguments);
    }

    return EXIT_SUCCESS;
}
```