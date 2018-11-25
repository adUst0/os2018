# Упражнение 8

---

## I. Условно изпълнение

 - `cmd1 && cmd2` - cmd2 се изпълнява, ако cmd1 завърши успешно
 - `cmd1 || cmd2` - cmd2 се изпълнява, ако cmd1 завърши неуспешно

---

## II. Работа със стрингове

@ul

 - `expr length <STRING>` - дължината на STRING 
 - `expr substr <STRING> <POS> <LENGTH>` - подстринг от STRING . Индексацията е от 1
 - `expr index <STRING> <CHARS>` - index in STRING where any CHARS is found, or 0

@ulend

---

## III. Функции

---

### 1. Създаване на фунцкия

```shell
function_name () {  
    списък_команди  
}

function function_name {  
    списък_команди  
}
```

---

### 2. Извикване на функция

```shell
# Create function
say_hello() {
    echo Hello World!
}

# Function invocation
say_hello # Output: Hello World!
```

---

### 3. Аргументи към функция

```shell
say_hello() {
    echo Hello, $1!
}

# Pass argument to a function
say_hello Student # Output: Hello, Student!
```

---

### 4. Return Values

- `return [N]` - прекратява изпълнението на функцията с код на завършване N (т.е. Bash ни позволява да връщаме само код на завършване)

Пример:

```shell
say_hello() {
    echo Hello, $1!
    return 5
    echo "after return" # this line will not be executed
}
```

---

### 5. Variable Scope

@ul

- По подразбиране всички променливи са **глобални**. 
- За да създадем локална променлива в дадена функция, използваме ключовата дума `local`

@ulend

---

Пример:

```shell
myfunc() {
    x=5
    local y=7
}

echo "<$x>" # Output: <>
echo "<$y>" # Output: <>

myfunc # creates global variable x

echo "<$x>" # Output: <5>
echo "<$y>" # Output: <>
```

---

## IV. Важни файлове

@ul

 - /etc/passwd - файл с информация за всички потребители
 - /dev/null - празен файл. Всичко, което пренасочим към него, изчезва. 
 - .bash_profile - КП с конфигурация за системата (изпълнява се при логическо включване)

@ulend

---

## Въпроси
