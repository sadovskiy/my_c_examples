/*
 * Пример реализации простой задачки FizzBuzz
 * Условие
 * Напишите программу, которая выводит на экран числа от 1 до 100.
 * При этом вместо чисел, кратных трём, программа должна выводить слово «Fizz»,
 * а вместо чисел, кратных пяти — слово «Buzz». Если число кратно и 3, и 5,
 * то программа должна выводить слово «FizzBuzz»
 */

#include <stdio.h>

int main()
{
    int array[100] = {0};

    for (int i = 0; i < 100; ++i) {
        array[i] = i;

        if (!(array[i] % 3))
            printf("fizz, ");
        else
            if (!(array[i] % 5))
                printf("Buzz, ");
            else
                printf("%d, ", array[i]);
        if (!(i % 10))
            printf("\n");

    }

    printf("\n");

    return 0;
}
