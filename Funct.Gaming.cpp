#include <iostream>

using namespace std;

int G(int x);
int F(int x)
{
    if ((x % 2 == 1) && (x <= 20))
        {
            return F(x/2) + G(x+6);
        }
        else return 1;
}

int G(int x)
{
    if ((x % 2 == 1) && (x <= 20))
        {
            return G(x*3) + F(x-1);
        }
        else return 1;
}

int main()
{
    setlocale(0,"RUS");
    cout << "Написать странную цифру " << F(5);
    return 0;
}
