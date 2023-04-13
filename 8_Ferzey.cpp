#include <iostream>

using namespace std;

    int doska[8][8];
    int q = 0;

void pokaz_Q()
{
    for(int a = 0; a < 8; ++a)
    {
        for(int b = 0; b < 8; ++b)
        {
            cout << ((doska[a][b]) ? "Q " : ". ");
        }
        cout << endl;
    }
}

bool proverka_Q(int a, int b)
{
    for(int i = 0; i < a; ++i)
    {
        if(doska[i][b])         return false;
    }
    for(int i = 1; i <= a && b-i >= 0; ++i)
    {
        if(doska[a-i][b-i])     return false;
    }
    for(int i = 1; i <= a && b+i < 8; i++)
    {
        if(doska[a-i][b+i])     return false;
    }
    return true;
}

void ustabovit_Q_na_dosku(int a)
{
    if(a == 8)
    {
        pokaz_Q();
        cout << "Итерация - " << ++q << endl << endl;
        return;
    }

    for(int i = 0; i < 8; ++i)
    {
        if(proverka_Q(a, i))
        {
            doska[a][i] = 1;
            ustabovit_Q_na_dosku(a+1);
            doska[a][i] = 0;
        }
    }
    return;
}

int main()
{
    setlocale(0,"");
    ustabovit_Q_na_dosku(0);

    return 0;
}
