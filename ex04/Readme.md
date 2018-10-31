# Упражнение 4

### Теми за контролно №1 (на 05.11) :

 - Файлова система
 - Команди за работа с файлове и директории
 - Информационни команди
 - Команди свързани с многопотребителския режим
 - Wildcards. Екраниране. Метасимволът `. 
 - Пренасочване. Конвейер. 
 - Асинхронно изпълнение на команди. 

## I. Редактор Vi

### 1. Режим на работа
1.  Command mode
2.  Insert mode

### 2. Движение по файла

 - Arrows

 CTRL + :
 - U - 1/2 стр. нагоре
 - D - 1/2 стр надолу
 - F - 1 стр. надолу
 - B - 1 стр. нагоре
 - H - началото на файла
 - L - края на файла

### 3. Записване и излизане

 - :w [f1] - save [as f1]
 - :q - exit
 - :wq - save and exit
 - :q! - discard changes and exit
 - :!cmd - execute bash command

### 4. Редактиране
|  | change | delete | move | copy |
|:--:|:--:|:--:|:--:|:--:|
| char | r | x | - | - |
| word | c[n]w | d[n]w | d[n]w -> p | y[n]w -> p |
| line | [n]cc | [n]dd | [n]dd -> p | [n]yy -> p |

### 5. Идентация

 - [n]>> - таб надясно [следващите n реда]
 - [n]<< - таб наляво [следващите n реда]

### 6. Търсене във файла

 - :/ABC/ - намира първото срещане
		- n - следващото срещане
		- N - предишното
		**NB.** Накрая на файла, почва от началото.

## II. Задачи
1. Напишете безкраен цикъл на C. Стартирайте програмата и я убийте през друг shell. 
2. Напишете команда, която отпечатва броя на сесиите на потребителя, който изпълнява командата.

		who | grep `whoami` | wc -l
		who | grep `whoami` -c