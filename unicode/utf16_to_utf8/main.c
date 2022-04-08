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
 * Программа демонстрирует алгоритм кодирования широких символов wchar_t
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Широкий_символ
 * https://ru.wikipedia.org/wiki/Locale.h
 * https://ru.wikipedia.org/wiki/Символьный_тип
 * https://ru.wikipedia.org/wiki/Printf
 * 
 * 
 */

#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

// Для MS Windows
#ifdef __WINNT__
#include <fcntl.h>
#include <io.h>
#endif

int main(void)
{
    // Устанавливаем локаль командной строки "язык_СТРАНА.Кодировка"
    // Для GNU/Linux
    #ifdef __linux__
    setlocale(LC_ALL, "ru_RU.UTF-8");// В MS Windows обычно пишется "rus"
    #endif
    
    // Для MS Windows
    #ifdef __WINNT__ // Для компилятора MSVC лучше использовать макрос _WIN64
    setlocale(LC_ALL, "rus");// или "Russian"
    #endif
    // Подробнее:
    // https://ru.wikipedia.org/wiki/Региональные_настройки_(программирование)
    // https://ru.wikipedia.org/wiki/Юникод
    // https://ru.wikipedia.org/wiki/UTF-8
    // https://habr.com/ru/post/138173


    // Создаём переменную "Широкий символ"(wch), у которого размер
    // может быть разный, но в большинстве систем это 4 байта (32 бита).
    // Какой фактический размер в вашей системе можно узнать
    // с помощью sizeof()
    wchar_t wch = 0;

    // Сообщение пользователю "Введите символ",
    // который будет записан в нашу переменную.
    wprintf(L"Input character (Введите символ): ");

    // Спецификаторы размера
    // Тут использован перед строкой префикс L (тип int64), так как по умолчанию
    // строка на Си в коде будет массивом типа данных char,
    // но функции wscanf() и wprintf() предназначены для работы с типом wchar_t

    // Есть ещё префикс U. Нужен для работы с типом char32_t,
    // но не на всех компиляторах работает

    // Коротко по типам на примере символа b (латиница) и б (кириллица)
    // Одиночный символ. В скобках код в десятичной форме.
    //  'b' (62)      'б' (не существует)   тип: char    (1 байт)
    // L'b' (00 62)  L'б' (04 31)           тип: wchar_t (2 байта)

    // Обратите внимание, wchar_t задействовал 2 байта из 4.
    // Остальные байты забиваются 0. Это происходит по тому,
    // что кодировка UTF-8 не постоянной, а переменной длинны.
    // В ней первый байт определяет сколько будет отведено
    // следующих байт на один символ

    // Массив символов (строка). Для примера будет состоять
    // из одного символа {'b', '\0'} или в десятичной форме {62, 0}
    //  "b"   тип: char[2]
    // L"b"   тип: wchar_t[2]
    // U"b"   тип: char32_t[2]

    // Запись символа в переменную "wch"

// Для MS Windows
#ifdef _WIN64
     _setmode(_fileno(stdin), _O_U16TEXT);
#endif

    wscanf(L"%Lc", &wch); // или wch = fgetwc(stdin);

    // Для корректного чтения широкого символа в вызов wscanf() также надо
    // добавить спецификатор размера L. L - long double

    // Покажем прочитанный символ
    wprintf(L"Character: %Lc\n", wch);

    // Покажем десятичный код
    // wprintf(L"Code dec: %d \n",  ch);
    // Но это плохой вариант. Не рекомендуется использовать
    // Надо писать так (с привидением типа)
    wprintf(L"Code dec: %d\n",  (int)wch);

    // Выведем константу 0x0431 (символ 'б')
    wprintf(L"Const character: %Lc\n", (char)0x0052);

    // Для наглядности разложим тип wchar_t на отдельные байты
    unsigned char byte1 = 0; // Для хранения первой части кода символа в UTF-8
    unsigned char byte2 = 0; // Второй
    unsigned char byte3 = 0; // Третей
    unsigned char byte4 = 0; // Четвёртой

    // Кодирование в UTF-8 на примере символа ' ' (пробел)
    //              00010100 - 20 -  30 (8 бит) - исходный символ
    // Символ имеет размер укладывающийся в 7 бит. Первый (по порядку)
    // бит не используется, а выступает как признак того,
    // что символ укладывается в один байт
    // и можно обойтись первой половиной таблицы ASCII.
    // Если он занят, то это значит надо задействовать двухбайтную таблицу
    // и раскодировка будет проходить как на следующем примере
    // с кириллической буквой 'а'

    // Некоторые байты в разных системах исчисления
    //       bin    - dec - Hex
    //    1110 0000 - 224 - E0
    //    1100 0000 - 192 - C0
    //    1000 0000 - 128 - 80
    //    0111 1111 - 127 - 7F
    //    0100 0000 -  64 - 40
    //    0011 1111 -  63 - 3F


    // Кодирование в UTF-8 на примере символа 'а' (кириллица) (11 бит)
    //    1-ый байт 2-ой байт
    //         100  00110000 -  1072 -  4 30   (4) (48) - 1)
    //    110       10       ---------------------------- 2)
    //    110       10110000 ---------------------------- 3)
    //    11010000  10110000 ---------------------------- 4)
    //    11010000  10110000 - 53424 - D0 B0 (208)(176) - 5)
    // В UTF-16 видно, что символ занимает явно больше 8 бит
    // 1) берём биты исходного символа
    // 2) создаём битовую маску UTF-8
    // 3) из второго байта берём последние шесть исходных разрядов
    //    и добавляем в по маске в последние шесть разрядов
    //    второго байта кодируемого символа
    // 4) остаётся шесть не распределённых разрядов (100000).
    //    Первые три (100) в первом байте и два (00) оставшихся
    //    в начале второго. Сдвигаем их на шесть разрядов вправо
    //    и полученные разряды пишем в первый байт
    // 5) оставшиеся места заполняем нулями и получаем итоговый результат

    // Кодирование в UTF-8 на примере символа '€' (знак евро) (14 бит)
    //    1-ый байт 2-ой байт 3-ий байт
    //                100000  10101100 -     8364 -    20 AC        (32) (172)
    //    1110      10        10       - маска UTF-8
    //    1110      10        10101100 - 1)
    //    1110      10000010  10101100 - 2)
    //    1110  10  10000010  10101100 - 3)
    //    11100010  10000010  10101100 - 14844588 - E2 82 AC (226) (130) (172)
    // Так как часть действий повторяется возьмём только значимые этапы
    // 1) как и прошлый раз записываем шесть битов с конца в последний
    //    третий байт.
    // 2) оставшиеся разряды перемещаем вправо на эти шесть бит
    //    и пишем во второй байт (000010)
    // 3) так как они не умещаются в шесть бит второго байта. Остался хвост
    //    в два бита (10). То мы снова двигаем их ещё дальше. Уже на 12 бит.
    //    Записываем хвост в первый байт


    // Для символа больше трёх байт алгоритм работает аналогично.
    // Ниже представлены несколько символов, которые можно использовать
    // для контрольной проверки алгоритма
    //                     1  00000011  01001000 - 66376 - 1 03 48 '𐍈'
    //    1-ый байт 2-ой байт 3-ий байт 4-ый байт
    //    11110     10        10        10
    //
    //    11110000  10010000  10001101  10001000 - F0 90 8D 88
    //
    //                     1  11110101  01110100 - 128372 - 1 F5 74 '🕴'
    //    11110     10        10        10
    //    11110     10 11111  10        10
    //    11110000  10011111  10010101  10110100 - F0 9F 95 B4


    if (wch < 0x80) // Выясняем сколько занимает бит символ
        byte1 = wch; // Для однобайтных символов (меньше восьми бит)
    else
        if (wch < 0x0800) { // Для символов меньше 16 бит
            byte2 = 0x40 ^ (0xC0 | wch); // Пункт 3) из описания
            byte1 = 0xC0 | (wch >> 6);   // Пункт 4)
        }
        else
            if (wch < 0xFFFF) { // Для символов меньше 24 бит
                byte3 = 0x40 ^ (0xC0 | wch); // Пункт 1)
                byte2 = 0x40 ^ (0xC0 | (wch >> 6)); // Пунк 2)
                byte1 = 0xE0 | (wch >> 12);// Пункт 3)
            }
            else
                if (wch < 0xFFFFFF) { // Для символов меньше 32 бит
                    byte4 = 0x40 ^ (0xC0 | wch);// Пункт 1)
                    byte3 = 0x40 ^ (0xC0 | (wch >>  6));// Пункт 2)
                    byte2 = 0x40 ^ (0xC0 | (wch >> 12));// Пункт 3)
                    byte1 = 0xF0 | (wch >> 24); // Делаем так же как в 3)
                }
                else {
                    // На случай если встретиться, что-то больше 32 бит
                    wprintf(L"Error: encoding is too big!");
                    return EXIT_FAILURE;
                }
    // Небольшое пояснение как работает вставка шести битов в байт
    // byte2 = 0x40 ^ (0xC0 | wch)
    // 1100 0000 - 0xC0          1111 0101
    //     |                         ^
    // 1111 0101 - wch (F5)      0100 0000 - 0x40
    //     =                         =
    // 1111 0101                 1011 0101 - byte2 (B5)
    // Таким образом в переменной byte2 будет значение согласно маске UTF-8



    // Для вывода hex код в UTF-8
    wprintf(L"Code hex UTF-8: %X %X %X %X\n",  byte1, byte2, byte3, byte4);

    // Hex код в шестнадцатеричной системе
    wprintf(L"Code hex UTF-16: %04X\n", (int)wch);
    wprintf(L"Size: %zu Byte\n", sizeof (wch));

    return 0;
}
