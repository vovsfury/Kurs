#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "List.h"
#include "Edmonds-Karp.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream read;
	unsigned MaxFlow = 0;
	string file_name = "test.txt";
	read.open(file_name, ios::in);
	if (read.bad())
	{
		cout << "������! ���� �� ��������.";
		return 0;
	}
	cout << "������������! ��� ������������ ���������, ������� ���� ������������ ����� � ������������ ����." << endl;
	cout << "������������ ���� ����� �� �����: " << file_name << endl << endl;
	Process(MaxFlow, read);
	cout << "������������ ����� � ������������ ���� �����: " << MaxFlow << endl;
	read.close();
	return 0;
}