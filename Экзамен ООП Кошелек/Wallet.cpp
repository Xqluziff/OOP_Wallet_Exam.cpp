#include "Wallet.h"
#include <fstream>
#include <vector>
#include <string>
#include <io.h>


void Wallet:: Print()
{
	cout << "----------------------------------\n";
	cout << "������ �����:\t|  " << Debit_Cash <<" �." <<endl;
	cout << "������ ������:\t|  " << Credit_Cash <<" �." <<endl;
	cout << "----------------------------------\n";
}

void Wallet::Rec_operation(const float&temp_cash,const string& operation_category,const int uCard)   
{
	fstream Save_operation;

	if (uCard==1)
	{
		Save_operation.open("Debit operation.txt",fstream::app);
		if (!Save_operation.is_open())
		{
			cout << "Error !";
		}
		else
		{
			Save_operation << d.GetYear() << " " << d.GetMonth() << " " << d.GetDay() << ";" << temp_cash << ";" << operation_category << "\n";
			Save_operation.close();
		}
	}
	else if (uCard == 2)
	{
		Save_operation.open("Credit operation.txt",fstream::app);
		if (!Save_operation.is_open())
		{
			cout << "Error !";
		}
		else
		{
			Save_operation << d.GetYear() << " " << d.GetMonth() << " " << d.GetDay() << ";" << temp_cash << ";" << operation_category << "\n";
			Save_operation.close();
		}
	}
}

void Wallet::Top_up_cash(int uCard)  
{
	int D, M, Y;

	if (uCard == 1) 
	{		
		float temp_cash;
		cout << "������� ����� ���������� ��������� �����\n";
		cin >> temp_cash;
		Debit_Cash += temp_cash;
		cout << "������� �����(01 01 2022) \n";
		cin >>D >> M >> Y;
		d.SetDay(D); d.SetMonth(M); d.SetYear(Y);		

		operation_category = "����������";

		Rec_operation(temp_cash, operation_category,uCard);
		cout << "�������� �������� ������� ��������� �� ��� ����\n\n";
	}
	if (uCard == 2)
	{
		float temp_cash;
		cout << "������� ����� ���������� ��������� �����\n";
		cin >> temp_cash;
		Credit_Cash += temp_cash;
		cout << "������� �����(01 01 2022) \n";
		cin >> D >> M >> Y;
		d.SetDay(D); d.SetMonth(M); d.SetYear(Y);
		operation_category = "����������";

		Rec_operation(temp_cash, operation_category, uCard);
		cout << "�������� �������� ������� ��������� �� ��� ����\n\n";
	}	
}

void Wallet::To_spend_cash(int uCard,string ux)  
{
	int D, M, Y;

	if (uCard==1)
	{
		float temp_cash;
		cout << "������� �����\n";
		cin >> temp_cash;
		cout << "������� �����(01 01 2022) \n";
		cin >> D >> M >> Y;
		d.SetDay(D); d.SetMonth(M); d.SetYear(Y);

		Debit_Cash -= temp_cash;

		if (Debit_Cash < 0)
		{
			cout << "\n\t������������ �������\n";
			Debit_Cash += temp_cash;
		}
		else
		{
			operation_category = ux;
			Rec_operation(temp_cash, operation_category,uCard);
			cout << "\n\t�������� ��������� ������� \n";
		}
	}

	if (uCard == 2)
	{
		float temp_cash;
		cout << "������� �����\n";
		cin >> temp_cash;
		cout << "������� �����(01 01 2022) \n";
		cin >> D >> M >> Y;
		d.SetDay(D); d.SetMonth(M); d.SetYear(Y);

		Credit_Cash -= temp_cash;

		if (Credit_Cash < 0)
		{
			cout << "\n\t������������ �������\n";
			Debit_Cash += temp_cash;
		}
		else
		{
			operation_category = ux;
			Rec_operation(temp_cash, operation_category, uCard);
			cout << "\n\t�������� ��������� ������� \n";
		}
	}
	

}

bool Wallet::Verification(string uLogin, string uPass)
{	
	Encryption(uLogin, uPass);

	fstream Var;
	Var.open("Account.txt" ,fstream::in);
	if (!Var.is_open())
	{
		cout << "Error file LogPass\n";
	}
	else
	{
		string tempLogin, tempPass;

		while (!Var.eof())
		{
			getline(Var, tempLogin, ' ');
			getline(Var, tempPass, '\n');
			if (uLogin == tempLogin)
			{
				if (uPass == tempPass)
				{
					cout << "\n\t�������� ���� � ��\n\n";
					return true;
				}
			}		
		}	
			cout << "\n\t�������� ����� ��� ������\n\n";
			return false;		
	}
	Var.close();
}

void Wallet:: �reating_an_account(string uNewLogin, string uNewPass)
{
	Encryption(uNewLogin, uNewPass);

	fstream Save_Account;
	Save_Account.open("Account.txt",fstream::app);
	if (!Save_Account.is_open())
	{
		cout << "\t������ ���������� ������� ������\n";
	}
	else
	{
		Save_Account << uNewLogin << " " << uNewPass<< "\n";
	}
	Save_Account.close();
}

void Wallet::Encryption(string &uNewLogin, string &uNewPass)
{
	char CodeLogin[20];
	char CodePass[20];

	for (int i = 0; i < uNewLogin.length(); i++)
	{
		CodeLogin[i] = uNewLogin[i]+=3;
	}

	for (int i = 0; i < uNewPass.length(); i++)
	{
		CodePass[i] = uNewPass[i]+=10;
	}
}

vector<search> Wallet::categoryes(vector<search>& selected)
{	
	search* cat = new search[3];
	int food = 0; int benz = 0; int shmot = 0;
	
	for (int i = 0; i < selected.size(); i++)
	{
		if (selected[i].GetType()=="���")
		{		
			food += selected[i].GetSum();
		}
		else if (selected[i].GetType() == "������")
		{
			benz += selected[i].GetSum();
		}
		else if (selected[i].GetType() == "������")
		{
			shmot += selected[i].GetSum();
		}	
	}
	cat[0].SetSum(food); cat[0].SetType("���");
	cat[1].SetSum(benz); cat[1].SetType("������");
	cat[2].SetSum(shmot); cat[2].SetType("������");	
	sortSum(cat, 3);
	selected.clear();

	for (int i = 0; i < 3; ++i)
	{
		selected.push_back(cat[i]);
	}
	return selected;
}

search& Wallet::sortSum(search* &mas,int usize)
{
	for (int i = 0; i < usize; i++)
		{
			for (int j = 0; j < usize - 1; j++)
			{
				if (mas[j].GetSum() < mas[j + 1].GetSum())
				{
					search t = mas[j];
					mas[j] = mas[j + 1];
					mas[j + 1] = t;
				}
			}
	}	
		return*mas;		
}

void Wallet:: Registration()
{
	string NewLogin, NewPass, NewPass_2;
	cout << "\t������� ���������� �����\n";
	cin >> NewLogin;

	do
	{
		cout << "\t������� ������\n";
		cin >> NewPass;
		cout << "\t������� ������ ��� ��� \n";
		cin >> NewPass_2;
		if (NewPass == NewPass_2)
		{
			cout << "\n�� ������� ������������������\n";
		}
		else
		{
			cout << "\t������ �� ���������!!!\n";
			cout << "\t���������� ������\n\n\n";
		}
	} while (!(NewPass == NewPass_2));
	
	�reating_an_account(NewLogin, NewPass);
}

int Wallet:: find_size_array(int ucard) //����� ����� � ����� ��� ������� �������
{
	fstream Save_operation;
	int size = 0;
	string tempDebit;
	if (ucard == 1)
	{
		Save_operation.open("Debit operation.txt", fstream::in);//fstream::in | fstream::app
	}
	else
	{
		Save_operation.open("Credit operation.txt", fstream::in);
	}

	while (getline(Save_operation, tempDebit))
	{
		size++;
	}
	Save_operation.close();
	return size;
}

search& Wallet::pars_file(search* & sortDate, int ucard, int size)
{
	fstream Save_operation;
	if (ucard == 1)
	{
		Save_operation.open("Debit operation.txt", fstream::in);
	}
	else
	{
		Save_operation.open("Credit operation.txt", fstream::in);
	}
	if (!Save_operation.is_open())
	{
		cout << "Error !";
	}
	else
	{
		string tempstr;

		for (int i = 0; i < size; i++)
		{
			getline(Save_operation, tempstr, ' ');
			sortDate[i].SetDateYear(stoi(tempstr));
			tempstr.clear();

			getline(Save_operation, tempstr, ' ');
			sortDate[i].SetDateMonth(stoi(tempstr));
			tempstr.clear();

			getline(Save_operation, tempstr, ';');
			sortDate[i].SetDateDay(stoi(tempstr));
			tempstr.clear();

			getline(Save_operation, tempstr, ';');
			sortDate[i].SetSum(stoi(tempstr));
			tempstr.clear();

			getline(Save_operation, tempstr, '\n');
			sortDate[i].SetType(tempstr);
			tempstr.clear();
		}
	}
	return *sortDate;
	Save_operation.close();
}

void Wallet::sort_date(search*& sortDate, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (sortDate[i].GetDate().GetYear() < sortDate[j].GetDate().GetYear() ||
				sortDate[i].GetDate().GetYear() == sortDate[j].GetDate().GetYear() &&
				sortDate[i].GetDate().GetMonth() < sortDate[j].GetDate().GetMonth() ||
				sortDate[i].GetDate().GetYear() == sortDate[j].GetDate().GetYear() &&
				sortDate[i].GetDate().GetMonth() == sortDate[j].GetDate().GetMonth() &&
				sortDate[i].GetDate().GetDay() < sortDate[j].GetDate().GetDay())																																													//sortDate[i].GetDay() > sortDate[j].GetDay())
			{
				search t = sortDate[j];
				sortDate[j] = sortDate[i];
				sortDate[i] = t;
			}
		}
	}	
}

void Wallet::report(int ucard, int what_report, Date time, int period) 
{
	int size = find_size_array(ucard); // ������� ���. ����� � ����� ��� ��������� ������ 

	search* sortDate = new search[size]; //����� ������ ��� �����
	vector<search>selected; // ������ ��� �������
	pars_file(sortDate, ucard, size); // ���� ����� � ����� ������(��� ��������)

	if (what_report == 1) //����� �� ����� ��� 
	{
		sortSum(sortDate, size);// ���������� ������ ������� �� �����
		selection(sortDate,selected, time, size, period);// ������� �� ������ ������� � ������ selected
		RecReport(selected,1);
	}
	else if (what_report == 2) //����� �� ��� ����������
	{	
		selection(sortDate, selected, time, size, period);
		categoryes(selected);
		RecReport(selected, 2);
	
	}
	else //����� ���� ������� �� ����� � ���������
	{
		sort_date(sortDate,size);
		selection(sortDate, selected, time, size, period);
		RecReport(selected,3);
	}
}

vector<search> Wallet::selection(search* sortDate,vector<search>& selected, Date time, int usize,int period)
{
	int calendar[13]{ 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int remaining_days;
	Date te; 
		
	if (period > 1)
	{
		if (period == 2){period = 7;}
		else if (period == 3){period = 30;}

		if (time.GetDay() < period)
		{
			int remaining_days = period - time.GetDay(); // ������� ���� �� ������������ �����
			te.SetDay(calendar[time.GetMonth() - 1] - remaining_days + 1);
			te.SetMonth(time.GetMonth() - 1);
			te.SetYear(time.GetYear());			// ���� ��������� ������� � ����������� �������
		}
		else
		{
			te.SetDay(time.GetDay() - period);
			te.SetMonth(time.GetMonth());
			te.SetYear(time.GetYear());			// ���� ��������� ������� � ����� ������
		}
		cout << "\n______________________________________\n";
		for (int i = 0; i < usize; i++)
		{
			if (sortDate[i].GetDate().GetYear() == time.GetYear() &&  //������� ��� ������ ������
				sortDate[i].GetDate().GetMonth() == time.GetMonth() &&
				sortDate[i].GetDate().GetDay() <= time.GetDay() &&
				sortDate[i].GetDate().GetDay() >= te.GetDay() ||
				sortDate[i].GetDate().GetYear() == time.GetYear() && //������� ��� 2� ������� 6 9 2022
				sortDate[i].GetDate().GetMonth() == time.GetMonth() &&
				sortDate[i].GetDate().GetDay() <= time.GetDay() ||
				sortDate[i].GetDate().GetYear() == time.GetYear() &&
				sortDate[i].GetDate().GetMonth() == te.GetMonth() &&
				sortDate[i].GetDate().GetDay() >= te.GetDay())
			{
				if (sortDate[i].GetType() == "���" || sortDate[i].GetType() == "������" || sortDate[i].GetType() == "������")
				{
					/*cout << sortDate[i].GetDate().GetDay() << "." << sortDate[i].GetDate().GetMonth() << "." << sortDate[i].GetDate().GetYear() << "\t" <<
						sortDate[i].GetSum() << "\t" << sortDate[i].GetType() << endl;*/
					selected.push_back(sortDate[i]);					
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < usize; i++)
		{
			if (sortDate[i].GetDate().GetYear() == time.GetYear() &&  //������� ��� ������ ������
				sortDate[i].GetDate().GetMonth() == time.GetMonth() &&
				sortDate[i].GetDate().GetDay() == time.GetDay())				
			{
				if (sortDate[i].GetType() == "���" || sortDate[i].GetType() == "������" || sortDate[i].GetType() == "������")
				{
					/*cout << sortDate[i].GetDate().GetDay() << "." << sortDate[i].GetDate().GetMonth() << "." << sortDate[i].GetDate().GetYear() << "\t" <<
						sortDate[i].GetSum() << "\t" << sortDate[i].GetType() << endl;*/
					selected.push_back(sortDate[i]);					
				}
			}
		}		
	}
	return  selected;	
}

void Wallet::RecReport(vector<search>& selected,int what_report)
{
	int count = 0;
	fstream Rec;
	Rec.open("RecReport.txt", fstream::app);
	if (!Rec.is_open())
	{
		"Error RecReport\n";
	}
	else
	{
		Rec << "__________Report___________\n";
			
			if (what_report == 1)
			{					
				for (int i = 0; i < selected.size(); ++i)
				{
					Rec << selected[i].GetDate().GetDay() << "." << selected[i].GetDate().GetMonth() << "." << selected[i].GetDate().GetYear() << ";" <<
						selected[i].GetSum() << ";" << selected[i].GetType() << endl;
					count++;
					if (count == 3) { break; }
				}
			}
			else if (what_report == 2)
			{
				
				for (int i = 0; i < selected.size(); ++i)
				{
					Rec << selected[i].GetSum() << ";" << selected[i].GetType() << endl;
					count++;
					if (count == 3) { break; }
				}
			}
			else
			{
				for (int i = 0; i < selected.size(); ++i)
				{
					Rec << selected[i].GetDate().GetDay() << "." << selected[i].GetDate().GetMonth() << "." << selected[i].GetDate().GetYear() << ";" <<
						selected[i].GetSum() << ";" << selected[i].GetType() << endl;
				}				
			}					
		Rec << "___________________________\n";		
		cout << "����� ������� �������� � ����\n";
	}
}










