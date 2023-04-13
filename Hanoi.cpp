#include <iostream>

using namespace std;

void move(int n, int a, int b)
{
    int check = 6 - a - b;
    if (n > 0) {
        if (a + b == 4) {
            move(n, a, 2);
            move(n, 2, b);
        }
        else {
            move(n - 1, a, check);
            cout <<   n   << "-ое по величине кольцо с "
                 <<   a   << " стержня вставить в "
                 <<   b   << " стержень" << endl;

            move(n - 1, check, b);
        }
    }
}

int main()
{
    int n;
    setlocale(0,"");
    cout << "Сколько колец - ";
    cin >> n;
    move(n, 1, 3);
}
