#include <iostream>
#include <Windows.h>

using namespace std;

//  12. Преобразовать строку таким образом, чтобы все слова в ней были напечатаны наоборот.

int main()
{
    setlocale(0,"");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string stroka;
    cout << "Исходная строка - ";
    getline(cin, stroka);
    string obr_stroka = stroka;
    int k = 0;
    for (int i = stroka.size()-1; i >= 0; i--)
    {
        obr_stroka[k] = stroka[i];
        k++;
    }
    cout << "Обратная строка - " << obr_stroka;
    return 0;
}
