#pragma once
#include <iostream>
#include <vector> //тут не было))))
using namespace std;



class Date
{
protected:
	int day;
	int month;
	int year;

public:
	Date(int d, int m, int y) :day{ d }, month{ m }, year{ y }{};
	Date() :Date(0, 0, 0) {};

	int GetDay() { return day; };
	int GetMonth() { return month; };
	int GetYear() { return year; };

	void SetDay(int d) { day = d; };
	void SetMonth(int m) { month = m; };
	void SetYear(int y) { year = y; };
};

class search
{
	Date date;
	float sum;
	string type;
public:
	Date GetDate() { return date; };
	float GetSum() { return sum; };
	string GetType() { return type; };

	void SetSum(float summa){sum = summa;}
	void SetType(string utype){type = utype;}
	void SetDateDay(int x){date.SetDay(x);		}
	void SetDateMonth(int x){date.SetMonth(x);}
	void SetDateYear(int x){date.SetYear(x);}
};

class Wallet
{
	float Debit_Cash;
	float Credit_Cash;
	string operation_category;
	Date d;
public:
	Wallet() :Debit_Cash{ 0 }, Credit_Cash{ 100000 }, operation_category{ "No"}, d{}{};
	~Wallet() {};

	//--------------Операции с картами-----------------
	void Print();         //Вывод баланса карт
	void Top_up_cash(int uCard);    //Пополненеие баланса
	void To_spend_cash(int uCard, string ux);  // Снятие наличных 
	void Rec_operation(const float& temp_cash, const string& operation_category,const int uCard); // Запись операции в файл


	//---------------Операции с Log/Pass----------------
	bool Verification(string uLogin,string uPass);  //Проверка логина и пароля в файле
	void Registration();  // Регистрация акаунта
	void Сreating_an_account(string uNewLogin,string uNewPass); //  Сохранение акаунта в файл(+ширф)
	void Encryption(string &uNewLogin, string &uNewPass);	//  Штфрование Log/Pass (цезарь) 


	//--------------Операции с отчетами------------------
	vector<search> categoryes(vector<search>& selected);  //Выборка отчета по категориям
	search& sortSum(search* &mas,int usize);   //Сортировка отчета по сумме
	int find_size_array(int ucard);    //Поиск количества строк в файле операций.  return размера массива
	search& pars_file(search*& sortDate, int ucard, int size);    //Парс файла операций в массив
	void sort_date(search*& sortDate, int size);   // Сортировка массива операций по дате
	void report(int ucard,int what_report,Date time,int t);// Вывод отчета
	vector<search> selection(search* sortDate, vector<search>& W, Date time, int usize, int t); //Выборка операций по дате (1д/7д/30)
	void RecReport(vector<search>& selected, int what_report);	// Запись отчета в файл
};




