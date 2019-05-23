// ConsoleApplication33.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <set>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	multiset<__int64>S;
	__int64 num,s;
	char c;
	in >> num;
	for (int i = 0; i < num; i++) {
		in >> c;
		if (c == 'A') {
			in >> s;
			S.insert(s);
		}

		else if (c == 'D') {
			in >> s;
			S.erase(s);
		}

		else if (c == '?') {
			in >> s;
		   auto it =  S.find(s);
		   if (it == S.end()) {
			   // not found  
			   out << "N"<<endl;
		   }

		   else out << "Y" << endl;
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
