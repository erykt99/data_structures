#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <inipp.h> //u have to download inipp.h
#include<vector>


void bubblesort(int* numbers, int amount) {

	int temp;
	int n;// = amount - 1;
	int zmiana;
	do
	{
		zmiana = 0;
		n = amount - 1;
		do
		{
			n--;
			if (numbers[n] > numbers[n + 1])
			{
				temp = numbers[n + 1];
				numbers[n + 1] = numbers[n];
				numbers[n] = temp;
				zmiana = 1;
			}


		} while (n != 0);
	} while (zmiana != 0);
}

void insertionsort(int* numbers, int amount) {

	int temp;
	int j;
	for (int i = 1; i < amount; i++)
	{
		temp = numbers[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (temp < numbers[j])
				numbers[j + 1] = numbers[j];
			else
				break;
		}
		numbers[j + 1] = temp;
	}


} 

void quicksort(int* numbers,int x, int y) { 

	int i, j, v, temp;
	i = x;
	j = y;
	v = numbers[div(x + y, 2).quot];
	do
	{
		while (numbers[i] < v) i++;
		while (v < numbers[j]) j--;
		if (i <= j)
		{
			temp = numbers[i];
			numbers[i] = numbers[j];
			numbers[j] = temp;
			i++;
			j--;
		}
	}  while (i <= j);
	if (x < j) quicksort(numbers, x, j);
	if (i < y) quicksort(numbers, i, y);
}

void heapsort(int numbers[], int amount)
{
	//const int N = amount;
	int i, j, k, m, x;

	for (i = 2; i <= amount; i++)
	{
		j = i; k = j / 2;
		x = numbers[i];
		while ((k > 0) && (numbers[k] < x))
		{
			numbers[j] = numbers[k];
			j = k; k = j / 2;
		}
		numbers[j] = x;
	}

	for (i = amount; i > 1; i--)
	{
		std::swap(numbers[1], numbers[i]);
		j = 1; k = 2;
		while (k < i)
		{
			if ((k + 1 < i) && (numbers[k + 1] > numbers[k]))
				m = k + 1;
			else
				m = k;
			if (numbers[m] <= numbers[j]) break;
			std::swap(numbers[j], numbers[m]);
			j = m; k = j + j;
		}
	}
	/*
	for (int k = 0; k < amount; k++)
	{
		if (numbers[k] > numbers[k+1])
		{
			std::swap(numbers[k], numbers[k + 1]);
		}
		else 
		{
			break;
		}
	}
	*/
}

void countingsort(int* numbers, int n, int min, int max)
{
	using namespace std;
	int* counters = new int[max - min + 1];

	for (int x = 0; x < (max - min + 1); x++)
	{
		counters[x] = 0;
	}

	for (int x = 0; x < n; x++)
	{
		
		counters[numbers[x] - min]++;
	}


	int lastIndex = 0;
	for (int x = 0; x < (max - min + 1); x++)
	{
		int y;
		for (y = lastIndex; y < counters[x] + lastIndex; y++)
		{
			numbers[y] = x + min;
		}
		lastIndex = y;
	}
}

int* find(int* tab, int n)
{
	int* minAndMax = new int[2];
	minAndMax[0] = tab[0];
	minAndMax[1] = tab[0];

	for (int x = 0; x < n; x++)
	{
		if (tab[x] < minAndMax[0])
		{
			minAndMax[0] = tab[x];
		}
		if (tab[x] > minAndMax[1])
		{
			minAndMax[1] = tab[x];
		}
	}

	return minAndMax;

}



int main() {

	using namespace std;
	inipp::Ini<char> ini;
	std::ifstream is("input.ini");
	ini.parse(is);
	int i = 0;
	int amount = 1000000;
	string s;
	//string method;
	int loops = 1;
	double time = 0;
	string method;
	
	

	inipp::get_value(ini.sections["settings"], "amount", amount);
	inipp::get_value(ini.sections["settings"], "method", method);
	inipp::get_value(ini.sections["settings"], "loops", loops);
	//string method = "heapsort";
	int *numbers = new int[amount];
	

	
	
	ifstream file;
	file.open("liczby.txt");
	if (!file) { cout << "Error\n"; }

	for (i = 0; i < amount; i++)
	{
		getline(file, s, ',');
		numbers[i] = stoi(s);
	}

	auto start = chrono::steady_clock::now();
	

	for (int k = 0; k < loops; k++) {

		if (method == "bubble") {
			bubblesort(numbers, amount);
		}
		else if (method == "insert")
		{
			insertionsort(numbers, amount);
		}
		else if(method == "quick")
		{
			quicksort(numbers, 0, amount - 1);
		}
		else if (method == "kopiec")
		{
			heapsort(numbers-1, amount);
			//quicksort(numbers, 0, amount - 1);
		}
		else if (method == "zliczanie")
		{
		int* minAndMax = find(numbers, amount);
		countingsort(numbers, amount, minAndMax[0], minAndMax[1]);
		}
	}

	
	
	//int* minAndMax = find(numbers, amount);
	//countingsort(numbers, amount, minAndMax[0], minAndMax[1]);
	//heapsort(numbers-1, amount);
	auto end = chrono::steady_clock::now();



	ofstream outFile;
	outFile.open("posortowane.txt");
	outFile << "Sredni czas [ms] dla "<<amount<<" liczb" << endl << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
	for (int i = 0; i < amount; i++)
	{
		outFile << numbers[i] << endl;
	}

	ofstream outFile2;
	outFile2.open("czasy.csv", ios::app);
	outFile2 << (((chrono::duration_cast<chrono::milliseconds>(end - start).count())) / loops) << ";" <<amount <<";"<<method << endl;
	outFile2.close();
	outFile.close();

	delete[] numbers;

	

	return 1;
}

