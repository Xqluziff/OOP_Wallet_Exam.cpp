#pragma once
#include <iostream>
#include <vector> //��� �� ����))))
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

	//--------------�������� � �������-----------------
	void Print();         //����� ������� ����
	void Top_up_cash(int uCard);    //����������� �������
	void To_spend_cash(int uCard, string ux);  // ������ �������� 
	void Rec_operation(const float& temp_cash, const string& operation_category,const int uCard); // ������ �������� � ����


	//---------------�������� � Log/Pass----------------
	bool Verification(string uLogin,string uPass);  //�������� ������ � ������ � �����
	void Registration();  // ����������� �������
	void �reating_an_account(string uNewLogin,string uNewPass); //  ���������� ������� � ����(+����)
	void Encryption(string &uNewLogin, string &uNewPass);	//  ���������� Log/Pass (������) 


	//--------------�������� � ��������------------------
	vector<search> categoryes(vector<search>& selected);  //������� ������ �� ����������
	search& sortSum(search* &mas,int usize);   //���������� ������ �� �����
	int find_size_array(int ucard);    //����� ���������� ����� � ����� ��������.  return ������� �������
	search& pars_file(search*& sortDate, int ucard, int size);    //���� ����� �������� � ������
	void sort_date(search*& sortDate, int size);   // ���������� ������� �������� �� ����
	void report(int ucard,int what_report,Date time,int t);// ����� ������
	vector<search> selection(search* sortDate, vector<search>& W, Date time, int usize, int t); //������� �������� �� ���� (1�/7�/30)
	void RecReport(vector<search>& selected, int what_report);	// ������ ������ � ����
};




