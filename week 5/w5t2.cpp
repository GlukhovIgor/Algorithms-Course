// ALGOS.cpp: определяет точку входа для консольного приложения.
//

#include<iostream>
#include<fstream>
using namespace std;

ifstream ifstr("input.txt");
ofstream ofstr("output.txt");

void minHeapify(pair<int, int>* arr, int idx, int* size, int* arr2) {
	while (2 * idx + 1 < *size) {
		int l = idx * 2 + 1;
		int r = idx * 2 + 2;
		int smallest;
		if (l < *size && arr[l].first < arr[idx].first) {
			smallest = l;
		}
		else {
			smallest = idx;
		}
		if (r < *size && arr[r].first < arr[smallest].first) {
			smallest = r;
		}
		if (smallest != idx) {
			pair<int, int> tmp = arr[idx];
			arr[idx] = arr[smallest];
			arr[smallest] = tmp;
			arr2[arr[idx].second] = idx;
			arr2[arr[smallest].second] = smallest;
			idx = smallest;
		}
		else {
			break;
		}
	}
}

int getMin(pair<int, int>* arr, int* size, int* arr2) {
	int min = arr[0].first;
	arr[0] = arr[*size - 1];
	arr2[arr[0].second] = 0;
	(*size)--;
	minHeapify(arr, 0, size, arr2);
	return min;

}

void lowerElem(pair<int, int>* arr, int i, int& new_val, int* arr2) {
	arr[i].first = new_val;
	while (i > 0 && arr[i].first < arr[(i - 1) / 2].first) {
		pair<int, int> tmp = arr[i];
		arr[i] = arr[(i - 1) / 2];
		arr[(i - 1) / 2] = tmp;
		arr2[arr[i].second] = i;
		arr2[arr[(i - 1) / 2].second] = (i - 1) / 2;
		i = (i - 1) / 2;
	}

}

void addElem(pair<int, int>* arr, int& val, int* size, int& count, int* arr2) {
	(*size)++;
	arr[*size - 1].first = val;
	arr[*size - 1].second = count;
	arr2[count] = *size - 1;
	int i = *size - 1;
	while (i > 0 && arr[i].first < arr[(i - 1) / 2].first) {
		pair<int, int> tmp = arr[i];
		arr[i] = arr[(i - 1) / 2];
		arr[(i - 1) / 2] = tmp;
		arr2[arr[i].second] = i;
		arr2[arr[(i - 1) / 2].second] = (i - 1) / 2;
		i = (i - 1) / 2;
	}

}

/*void PrintArray(vector<int>& arr) {
for (int i = 0; i < arr.size(); i++) {
cout << arr[i] << " ";
}
cout << endl;
}*/

int main()
{
	int n;
	if (ifstr.is_open()) {
		ifstr >> n;
		pair<int, int>* arr = new pair<int, int>[n];
		int* help_arr = new int[n];
		//int* help_arr2 = new int[n];
		for (int i = 0; i < n; i++) {
			arr[i].first = 0;
			arr[i].second = 0;
			//help_arr2[i] = 0;
		}
		int arrSize = 0;
		int num1, num2, count = 1;
		char c;

		for (int i = 0; i < n; i++) {
			++count;
			ifstr >> c;
			if (c == 'A') {
				ifstr >> num1;
				addElem(arr, num1, &arrSize, count, help_arr);
				//help_arr[count] = num1;
				//cout << "After command A " << num1 << " array is:" << endl;
				//PrintArray(arr);
			}
			if (c == 'X') {
				if (arrSize == 0) {
					ofstr << "*\n";
				}
				else {
					ofstr << getMin(arr, &arrSize, help_arr) << "\n";
				}
				//cout << "After command X array is:" << endl;
				//PrintArray(arr);
			}
			if (c == 'D') {
				ifstr >> num1 >> num2;
				if (arrSize != 0) {
					int i = help_arr[num1 + 1];
					lowerElem(arr, i, num2, help_arr);
				}
				//cout << "After command D " << num1 << " " << num2 << " array is:" << endl;
				//PrintArray(arr);
			}
		}
		delete[] arr;
		ifstr.close();
		ofstr.close();
	}
	return 0;
}

