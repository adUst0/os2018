# Упражнение 9

## I. Системни примитиви за работа с файлове

### 1. Отваряне на файл
```c
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

**RETURN VALUE:** Файлов дескриптор или -1 при грешка

**flags:**
 - O_RDONLY  
 - O_WRONLY  
 - O_RDWR  
 - O_CREAT  
 - O_TRUNC  
 - O_APPEND  

**mode:** задава права на достъп на файла, в случай че се създава нов файл (т.е. ако не е указано O_CREAT, то mode се игнорира). Правата на новия файл са (mode & ~umask)


### 2. Затваряне на файл

```c
#include <unistd.h>

int close(int fd);
```

**RETURN VALUE:** 0 при успех, -1 при грешка 

### 3. Четене от файл

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

**RETURN VALUE:** 

- -1: при грешка
 - 0: при EOF
 - брой прочетени байтове


### 4. Писане във файл

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

**RETURN VALUE:** 

- -1: при грешка
 - брой записани байтове

### 5. Важни файлови дескриптори

 - 0: stdin
 - 1: stdout
 - 2: stderr

```c
read(0, buff, size); 
write(1, buff, size); 
```

## II. Обработка на грешки

```c
#include <stdio.h>
void perror(const char *str); 
// Отпечатва съобщение на stderr: str: + описание на последната
// получена грешка по време на изпълнение на системен примитив

#include <errno.h>
int errno; // код на последната грешка
```

## III. Задачи

1. Напишете програма на C, която работи като `cp f1 f2`

2. Напишете програма на C, която работи като `cat [f1 f2 ... fn]`