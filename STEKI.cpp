// STEKI.cpp : Реализация связного списка через стеки

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Stack
{
	string data;
	Stack* prev;
};

Stack* make_stack(int n)
{
	if (n == 0) return 0;
	
	
	else
	{
		string elem;
		Stack* top = nullptr;
		Stack* p = new Stack;
		cout << 1 << ") ";
		getline(cin, elem);
		p->data = elem;
		p->prev = nullptr;
		top = p;
		for (int i = 2; i <= n; i++)
		{
			Stack* h = new Stack;
			cout << i << ") ";
			getline(cin, elem);
			h->data = elem;
			h->prev = top;
			top = h;
		}
		return top;
	}
}

void print_stack(Stack* top)
{
	if (top == nullptr)
	{
		cout << "Стек пуст" << endl;
	}
	else
	{
		Stack* p = top;
		for (int i = 1; p != nullptr; i++)
		{
			cout << i << ") " << p->data << endl;
			p = p->prev;
		}
	}
}

string pop(Stack*& top)
{
	Stack* p = top;
	int schet = 0;
	while (p != nullptr)
	{
		schet++;
		p = p->prev;
	}
	p = top;
	if (schet == 1)
	{
		string t = top->data;
		delete p;
		top = nullptr;
		return t;
	}
	else
	{
		Stack* t = p->prev;
		string u = p->data;
		top = t;
		delete p;
		return u;
	}
}

Stack* push(Stack*& top, string val)
{
	Stack* p = new Stack;
	p->data = val;
	p->prev = top;
	top = p;
	return top;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int kol_vo_elem;
	cout << "Сколько элементов в стеке - "; (cin >> kol_vo_elem).get();
	if (kol_vo_elem < 1) { cout << "Неправильное количество" << endl; return 0; }

	cout << "Введите элементы (они будут в обратном порядке):" << endl; Stack* st = make_stack(kol_vo_elem);
	string menu[4]
	{
		"Меню",
		"1) Удалить элемент стека",
		"2) Добавить К элементов в стек",
		"3) Вывести стек на экран"
	};

	bool loop = true;
	int vibor;

	string delete_elem;
	string new_elem;

	int K_plus_elem;
	int K_INDEX;

	Stack* st2 = make_stack(0);

	while (loop == true)
	{
		for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
		{
			cout << menu[i] << endl;
		}
		cout << "Выбор - "; (cin >> vibor).get();
		if (vibor > 0 && vibor < 4)
		{
			if (vibor == 1)
			{
				cout << "Элементы стека:" << endl; print_stack(st);
				cout << "Ключ для удаления - "; getline(cin, delete_elem);
				int k = 0;

				for (int i = 0; i < kol_vo_elem; i++)
				{
					string t = pop(st);
					if (t != delete_elem)
					{
						push(st2, t);
					}
					else
					{
						k = k + 1;
					}
				}
				kol_vo_elem -= k;
				for (int i = 0; i < kol_vo_elem; i++)
				{
					string t = pop(st2);
					push(st, t);
				}

				system("pause");
				system("cls");
			}
			if (vibor == 2)
			{
				cout << "Элементы стека:" << endl; print_stack(st);
				cout << "Сколько К элементов на добавление - "; (cin >> K_plus_elem).get();
				cout << "Номер элемента, перед которым нужно добавить - "; (cin >> K_INDEX).get();
				for (int i = 0; i < kol_vo_elem - K_INDEX + 1; i++)
				{
					string t = pop(st);
					push(st2, t);
				}

				cout << "Введите элементы:" << endl;
				for (int i = 0; i < K_plus_elem; i++)
				{
					getline(cin, new_elem);
					push(st, new_elem);
				}

				for (int i = 0; i < kol_vo_elem - K_INDEX + 1; i++)
				{
					string t = pop(st2);
					push(st, t);
				}

				system("pause");
				system("cls");
			}
			if (vibor == 3)
			{
				cout << "Элементы стека:" << endl; print_stack(st);
				system("pause");
				system("cls");
			}
		}
		else
		{
			cout << "Выход" << endl;
			loop = false;
		}
	}
}

