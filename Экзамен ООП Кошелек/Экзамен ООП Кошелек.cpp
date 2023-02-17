#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Wallet.h"
#include <windows.h>
using namespace std;


void main()
{
	setlocale(0,"");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Wallet MyFinans;
	int Card;
	
	cout << "\tВыберите действие \n";
	cout << "\t1-Создать учетную запись \n";
	cout << "\t2-Войти в ЛК \n";
	int temp;
	cin >> temp;
	if (temp==1)
	{
		MyFinans.Registration();
	}
	else
	{
		string Login, Pass;
		do
		{
			cout << "\n\tВведите логин и пароль(через пробел)\n";
			cin >> Login >> Pass;

		} while (!(MyFinans.Verification(Login, Pass)));
	}

	MyFinans.Print();
	int Operation;
	do
	{	
		cout << " С какой карты Вы хотите совершить операцию ?\n";
		cout << "\t1-Дебетовая\t 2-Кредитная\n";
		cin >> Card;

		cout << "Какую операцию желаете произвести? \n";
		cout << "\t 1-Пополнить баланс\n\t 2-Снять наличные\n\t 3-Совершить покупку\n\t 4-Статистика\n\t 0-Выход\n";		
		cin >> Operation;
		
		if (Operation == 1)
		{			
			MyFinans.Top_up_cash(Card);
			MyFinans.Print();
		}
		else if (Operation == 2)
		{			
			MyFinans.To_spend_cash(Card, "Снятие наличных");
			MyFinans.Print();
		}
		else if (Operation == 3)
		{
			string x;
			cout << "Какую покупку Вы собираетесь совершить?(Текст) \n";
			cout << " Еда\n Одежда\n Бензин\n";
			cin >>x;
			
			MyFinans.To_spend_cash(Card,x);
			MyFinans.Print();
		}
		else if(Operation==4)
		{			
			int what_report, period, D, M, Y;
			cout << "\tКакой отчет сформировать?\n";
			cout << "\t1-ТОП-3 затрат\t 2-ТОП-3 категорий\t3-Затратам и катагориям\t";
			cin >> what_report;//2
		
				cout << "За какой период фрормировать отчет\n";
				cout << "\t 1-День\t 2-Неделя\t 3-Месяц\n";
				cin >> period;//2
				cout << "От какого числа сформировать отчет(dd mm yyyy )\n";
				cin >> D >> M >> Y;;
				Date time(D, M, Y);
				
				MyFinans.report(Card, what_report, time, period);						
		}
	} while (Operation != 0  );
	
}

