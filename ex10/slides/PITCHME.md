# Упражнение 10

---

## I. Системни примитиви за работа с файлове (продължение)

---

### 1. Позициониране във файл

```c
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

**Възможни стойности на whence:**
 - SEEK_SET - спрамо началото  
 - SEEK_CUR - спрямо текущата позиция  
 - SEEK_END - спрямо края  

---

**RETURN VALUE:**
 - -1 при грешка
 - при успех - новия offset (в байтове) от началото на файла до текущата позиция

---

**NB.** Ако сме отворили файла с O_APPEND, можем да пишем само в края. 

---

Извадка от документацията на `open(2)`:

> `O_APPEND`  
> The file is opened in append mode. Before each  `write(2)`, the file offset is positioned at the end of the file, as if with  `lseek(2)`.

---

## II. Системни примитиви за работа с процеси

---

### 1. fork() - създава нов процес, копирайки текущия. (двата процеса се развиват незавизимо)

``` c
#include <unistd.h>

pid_t fork(void);
```

**RETURN VALUE:**
 - -1 при грешка
 - 0 в детето
 - в родителския процес , връща PID на новия процес

---

```c
if (fork() == 0) {
// child
}
else {
// parrent
}
```
---

### 2. PID на текущия / родителския процес

```c
#include <sys/types.h>
#include <unistd.h>

pid_t getpid(void); // връща PID на текущия процес
pid_t getppid(void); // връща PID на род. процес
```
**NB.**: Ако детето попита за PPID след като родителския процес е завършил вече, то getppid() ще върне 1. Това е така, защото след завършване на даден процес, всичките му деца стават дета на init процеса (който е с PID = 1)

---

**1. Задача**:  Напишете програма, която създава нов процес. В родителския и в новия процес отпечатва PID и PPID на викащия процес. 

---

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    int pid = fork();

    if (pid != 0) {
        printf("In parent: PID = %d\n", getpid());
        printf("In parent: PPID = %d\n", getppid());
        printf("In parent: child PID is: %d\n", pid);
    }
    else {
        sleep(3);
        printf("In child: PID = %d\n", getpid());
        printf("In child: PPID = %d\n", getppid());
    }

    return 0;
}
```

---

**2. Задача**: Какъв е изходът от програмата?

```c
int main() {

    int pid = fork();
    int i = 0;

    i++;
    if (pid != 0) {
        i++;
    }
    else {
        i += 2;
    }
    i++;

    printf("%d\n", i);

    return 0;
}
```

---

### 3. exec() family of functions -  replace the current process image with a new process image

```c
#include <unistd.h>

int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);

int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
```

При грешка, функцията връща -1. При успех, следващият код не се изпълнява. 

---

**Пример:** 
```c
execl("/bin/date", "date", 0);
execlp("ls", "ls", "-l", 0);

if (execlp("ls", "ls", 0) == -1) {
    perror("execlp");
}
else {
    printf("This line is never executed\n");
}
```

---

### 4. wait() - wait for process to change state

```c
#include <sys/types.h>
#include <sys/wait.h>

int main() {
...
    int status;
    pid_t wait(int &status);
...
}
```

---

### 5. exit() - cause normal process termination

```c
#include <stdlib.h>

void exit(int status);
```

---

## Задачи