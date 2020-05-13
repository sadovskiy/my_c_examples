/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует работу с обработкой сигналов POSIX
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/POSIX
 * https://ru.wikipedia.org/wiki/Сигнал_(Unix)
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void fall(const int n)
{
      int *p = 0;
      *p = n; // Создание аварийной ситуации, для демонстрации работы с сигналами
}

void posix_death_signal(int signum)
{
#ifdef __linux__
    // Совершаем необходимые действия перед закрытием приложения
    fprintf(stderr,"POSIX Signal received. Segmentation Fault!\n");
    raise(SIGSTOP);
    signal(signum, SIG_UNBLOCK);  // перепосылка сигнала
#endif

    // Выход из программы. Если не сделать этого,
    // то обработчик будет вызываться бесконечно.
    exit(EXIT_FAILURE);
}

int main(void)
{
    // после чего мы должны зарегистрировать этот обработчик:
    signal(SIGSEGV, posix_death_signal);

    // Функция где будет ошибка
    fall(10);

    fprintf(stdout,"Hello world!\n");

    return 0;
}



