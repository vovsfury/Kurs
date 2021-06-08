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
		cout << "Ошибка! Файл не открылся.";
		return 0;
	}
	cout << "Здравствуйте! Вас приветствует программа, которая ищет максимальный поток в транспортной сети." << endl;
	cout << "Транспортная сеть взята из файла: " << file_name << endl << endl;
	Process(MaxFlow, read);
	cout << "Максимальный поток в транспортной сети равен: " << MaxFlow << endl;
	read.close();
	return 0;
}