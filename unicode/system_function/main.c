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
 * Программа демонстрирует работу с вызовом функции system().
 * system запускает программу chcp командной строки MS Windows,
 * которая меняет кодовую страницу.
 * Для кодировки UTF-8 используется страница 65001.
 * Начиная с Windows 10 стало возможно включить UTF-8 на всю систему.
 * Если это сделать, то можно не пользоваться программой chcp.
 * Для этого надо отметить пункт "Бета-версия: Использовать Юникод (UTF-8)
 * для поддержки языка во всём мире". Как это сделать показано на снимках
 * экрана находящихся в каталоге с этой программой. Выполните действия
 * с 01 по 04 и перезагрузитесь. Для проверки включения UTF-8 откройте окно
 * командной строки MS Windows CMD и нажмите правой кнопкой указателя мыши
 * по заголовку окна. Откроются свойства как на снимке 04. Если всё верно,
 * то в поле "Текущая кодовая страница" будет написано "65001 (UTF-8)".
 * Дополнительно рекомендуется поставить шрифт "Lucida Console"
 * как на снимке 06.
 * Ниже описание пути к настройкам на англ.
 * All Settings -> Time & Language -> Language -> "Administrative Language Settings"
 * 
 * Узнать версию и сборку MS Windows можно командой "winver"
 * Пример окна показан на снимке экрана "Версия Windows.png"
 *
 * Команды CMD, такие как chcp, cls, pause работают только в MS Windows,
 * а команды Bash, такие как clear и read, только в GNU/Linux
 * 
 * Подробнее:
 * https://docs.microsoft.com/ru-ru/windows-server/administration/windows-commands/chcp
 * http://utf8everywhere.org/
 * https://devblogs.microsoft.com/commandline/windows-command-line-unicode-and-utf-8-output-text-buffer/
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
#ifdef __WINNT__ // или _WIN64 или __WIN64 или __WIN64__ и т.д.
    // system() запускает программу CMD "chcp" для смены текущей кодировки вывода на экран
    system("chcp 65001");
    // Начиная с ОС MS Windows 10 build 1903 можно, в языковых настройках панели управления, 
    // отметить пункт "Бета: использование Unicode UTF-8 для поддержки языков во всем мире" 
    // (англ. "Beta: Use Unicode UTF-8 for worldwide language support")
    // Подробнее в комментарии наверху.

    // А можно очистить экран командой CMD cls
    system("cls");
    
    // Или поставить на паузу
    system("pause");
    
    // У консольной программы chcp есть альтернатива, это использовать 
    // функции SetConsoleOutputCP(CP_UTF8) и  SetConsoleCP(CP_UTF8).
    // Делают они тоже самое. Описаны в заголовочном файле windows.h
    
#endif
    
#ifdef __linux__
    // В GNU/Linux можно очистить экран командой Bash "clear"
    system("clear");
    
    // Или поставить на паузу
    system("read");
    
#endif
    

    // Проверим смену кодировки распечатав текст на кириллице,
    // но хранящийся в кодировке UTF-8
    printf("Привет мир!\n");

    return 0;
}
