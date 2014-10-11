## Домашна работа 1

Решенията се предават по e-mail на следния адреси:

> kn201317@gmail.com

Срок за предаване: 16.10.2014 - 23.10.2014

Решението на всяка задача трябва да бъде под формата на файлове с окончание
*.cpp* и *.h* (не целите проекти, ако използвате Visual Studio). Файловете се
изпращат като attachment-и в mail-a. Освен решения на задачите самият mail
трябва да съдържа име и факултен номер. Успех!

### Задача

Дефинирайте шаблонен клас `PriorityQueue`, който представлява приоритетна опашка
с елементи, сортирани по даден приоритет. Нека елементите са от вида:

```c++
template <typename V, typename P>
struct Pair
{
    V value;
    P priority;
};

```

* `value` - стойност
* `priority` - приоритет, по който да се сортират

Действията, които може да извършваме върху един сортиран списък, са:

* `insert` - включва елемент към опашката по зададена стойност и приоритет
* `pop` - връща `true` и стойноста на елемента с най-голям приоритет като
аргумент (и го премахва) или `false`, ако няма елементи в опашката
* `peek` - връща стойноста на елемента с най-голям приоритет
* `empty` - връща `true/false` в зависимост от това дали опашката е празна или
не

За реализирането на класа използвайте максимален `Heap`, като реализирате всички
необходими методи за него и канонична четворка.