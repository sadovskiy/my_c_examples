#include <string>
#include <iostream>

using namespace std;

/// Латинский алфавит начинается после пробела
const uint64_t firstSymbol = L' '; // 32
const uint64_t numberOfCharacters = 95;

void GammaCoding( wstring &input, wstring &gamma, wstring &result )
{
    result.clear();
    for(auto i = input.begin(), j = gamma.begin();
        i < input.end();
        i++,
        j++ )
    {
        if(j == gamma.end())
            j = gamma.begin();
        auto Ti = *i - firstSymbol;
        auto Gi = *j - firstSymbol;
        auto s = Ti + Gi;
        auto r = firstSymbol + s % numberOfCharacters;
        result.push_back(r);
    }
}

void GammaDecoding( wstring &input, wstring &gamma, wstring &result )
{
    result.clear();
    for(auto i = input.begin(), j = gamma.begin();
        i < input.end();
        i++,
        j++ )
    {
        if(j == gamma.end())
            j = gamma.begin();
        auto Ci = *i - firstSymbol;
        auto Gi = *j - firstSymbol;
        auto s = Ci - Gi + numberOfCharacters;
        auto r = firstSymbol + s % numberOfCharacters;
        result.push_back(r);
    }
}

int main()
{
    locale::global(locale("ru_RU.UTF-8"));

    wstring str1, gamma, rez;

    wcout << L"Введите исходное сообщение: ";
    wcin >> str1;
    wcout << L"Введите гамму: ";
    wcin >> gamma;

    GammaCoding( str1, gamma, rez );
    wcout << L"Зашифрованное сообщение: ";
    wcout << rez << endl;

    wcout << L"Введите зашифрованное сообщение: ";
    wcin >> rez;

    GammaDecoding( rez, gamma, str1 );
    wcout << L"Исходное сообщение: ";
    wcout << str1 << endl;

    return 0;
}
 
