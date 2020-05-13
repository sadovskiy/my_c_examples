/*
 *
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * В программе показан пример функции вывода широких символов
 * в консоль MS Windows.
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Широкий_символ
 * https://ru.wikipedia.org/wiki/Символьный_тип
 * https://docs.microsoft.com/en-us/windows/console/writeconsole
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN64
#include <windows.h>
#endif

int main(void)
{
    wchar_t * wstr = L"Привет мир!\n";
    // Функция WriteConsoleW() работает аналогично функции ReadConsole()
    // из примера WideCharToMultiByte
#ifdef _WIN64
    DWORD written;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), wstr, wcslen(wstr) + 1, &written, 0);
#endif
    
    return 0;
}
