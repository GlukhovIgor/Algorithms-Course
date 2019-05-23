// ALGOS.cpp: определяет точку входа для консольного приложения.
//

#include<iostream>
#include<fstream>

using namespace std;

ifstream ifstr("input.txt");
ofstream ofstr("output.txt");
int ceil(int x, int y) {
	return x / y + (x % y != 0);
}

int main()
{
	int n;
	if (ifstr.is_open()) {
		ifstr >> n;
		int* arr = new int[n];
		bool flag = true;
		for (int i = 0; i < n; i++) {
			ifstr >> arr[i];
			if (i >= 1 && arr[i] < arr[ceil(i, 2) - 1]) {
				//cout << "apparently, " << arr[i] << " < " << arr[i / 2] << endl;
				flag = false;
				break;
			}
		}
		flag ? ofstr << "YES" : ofstr << "NO";
		delete[] arr;
		ifstr.close();
		ofstr.close();
	}
	return 0;
}

