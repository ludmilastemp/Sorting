#include <iostream> 
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

int n;
int p;
int stime;
std::vector<int> mass(100000);
//int mass[1000000];
std::vector<vector<int>> massr(100000, vector<int>(2));
//int massr[100000][2];
int a[1000000];

/*
void MergeSort(int lhs, int rhs) {
	for (int i = lhs; i < rhs + 1; ++i) a[i] = mass[i];
	int i = lhs; int j = (rhs + lhs) / 2 + 1; int k = lhs;
	while (k < rhs && i < (rhs + lhs) / 2 + 1 && j < rhs + 1) {
		if (a[i] <= a[j]) {
			mass[k] = a[i];
			++i;
		}
		else {
			mass[k] = a[j];
			++j;
		}
		++k;
	}
	while (i < (rhs + lhs) / 2 + 1) {
		mass[k] = a[i];
		++i;
		++k;
	}
	while (j < rhs + 1) {
		mass[k] = a[j];
		++j;
		++k;
	}
}

/*void MergeSort(int lhs, int rhs) {
	int a[100000];
	int b[100000];
	for (int i = 0; i < (rhs + lhs) / 2 - lhs + 1; ++i) {
		a[i] = mass[lhs + i];
	}
	for (int i = 0; i < rhs - (rhs + lhs) / 2; ++i) {
		b[i] = mass[(lhs + rhs) / 2 + 1 + i];
	}
	int i = 0; int j = 0; int k = lhs;
	while (k < rhs && i < (rhs + lhs) / 2 - lhs + 1 && j < rhs - (rhs + lhs) / 2) {
		if (a[i] <= b[j]) {
			mass[k] = a[i];
			++i;
		}
		else {
			mass[k] = b[j];
			++j;
		}
		++k;
	}
	while (i < (rhs + lhs) / 2 - lhs + 1) {
		mass[k] = a[i];
		++i;
		++k;
	}
	while (j < rhs - (rhs + lhs) / 2) {
		mass[k] = b[j];
		++j;
		++k;
	}
}* 
//старый вариант на двух доп массивах

void Merge(int lhs, int rhs) {
	if (lhs == rhs) return;
	Merge(lhs, (lhs + rhs) / 2);
	Merge((lhs + rhs) / 2 + 1, rhs);
	MergeSort(lhs, rhs);
	return;
}

void MergeMain(ofstream &fout)
{
	//for (int i = 0; i < n; ++i) mass[i] = rand() % 10000000 - 20000;
	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<int> uni(-2147483647, 2147483647);
	for (int i = 0; i < n; ++i) mass[i] = uni(rng);
	int lhs = 0;
	int rhs = n - 1;
	auto begin = std::chrono::high_resolution_clock::now();
	Merge(lhs, rhs);
	auto end = std::chrono::high_resolution_clock::now();
	/*for (int i = 0; i < n - 1; ++i)
		if (mass[i] > mass[i + 1]) {
			for (int j = 0; j < n; ++j)
				cout << mass[j] << " ";
			throw "Merge is wrong";
	}*
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	//for (int i = 0; i < n; ++i) cout << mass[i] << " ";
	//cout << endl << time.count() << endl;
	stime += time.count();
	//fout << "," << time.count();
}

/*void RadixSort() {
	int a[65536];
	for (int i = 0; i < 65536; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) ++a[mass[i] >> 0 & 65535];
	for (int i = 1; i < 65536; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[mass[i] >> 0 & 65535]] = mass[i];
	for (int i = 0; i < n; ++i) mass[i] = b[i];
}

void RadixSort1() {
	int a[65536];
	int k = 0;
	for (int i = 0; i < 65536; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) {
		++a[mass[i] >> 16 & 65535];
		if (mass[i] >> 16 & 65535 > 32767) ++k;
	}
	for (int i = 1; i < 65536; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[mass[i] >> 16 & 65535]] = mass[i];
	for (int i = 0; i < k; ++i) mass[i] = b[n - k + i];
	for (int i = 0; i < n - k; ++i) mass[i + k] = b[i];
}

void RadixMain(ofstream& fout) {
	for (int i = 0; i < n; ++i) mass[i] = rand() % 10000000 - 20000;
	/*std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<int> uni(-2147483647, 2147483647);
	//for (int i = 0; i < n; ++i) mass[i] = uni(rng);
	auto begin = std::chrono::high_resolution_clock::now();
	RadixSort();
	RadixSort1();
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	//for (int i = 0; i < n; ++i) cout << mass[i] << " ";
	//cout << endl << time.count() << endl;
	stime += time.count();
	fout << "," << time.count();
}*
//Radix 2-байтовый на одномерном массиве

/*void RadixSort() {
	int a[65536];
	for (int j = 0; j < n; ++j) massr[j][1] = massr[j][0] >> 0 & 65535;
	for (int i = 0; i < 65536; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) ++a[massr[i][1]];
	for (int i = 1; i < 65536; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[massr[i][1]]] = massr[i][0];
	for (int i = 0; i < n; ++i) massr[i][0] = b[i];
}

void RadixSort1() {
	int a[65536];
	int k = 0;
	for (int j = 0; j < n; ++j) massr[j][1] = massr[j][0] >> 16 & 65535;
	for (int i = 0; i < 65536; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) {
		++a[massr[i][1]];
		if (massr[i][1] > 32767) ++k;
	}
	for (int i = 1; i < 65536; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[massr[i][1]]] = massr[i][0];
	for (int i = 0; i < k; ++i) massr[i][0] = b[n - k + i];
	for (int i = 0; i < n - k; ++i) massr[i + k][0] = b[i];
}

void RadixMain(ofstream& fout) {
	for (int i = 0; i < n; ++i) massr[i][0] = rand() % 10000000 - 20000;
	/*std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<int> uni(-2147483647, 2147483647);
	//for (int i = 0; i < n; ++i) mass[i] = uni(rng);
	auto begin = std::chrono::high_resolution_clock::now();
	RadixSort();
	RadixSort1();
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	//for (int i = 0; i < n; ++i) cout << massr[i][0] << " ";
	//cout << endl << time.count() << endl;
	stime += time.count();
	fout << "," << time.count();
}*
//Radix 2-байтовый на двумерном массиве

void RadixSort() {
	int a[256];
	for (int i = 0; i < 256; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) ++a[mass[i] >> p & 255];
	for (int i = 1; i < 256; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[mass[i] >> p & 255]] = mass[i];
	for (int i = 0; i < n; ++i) mass[i] = b[i];
}

void RadixSort1() {
	int a[256];
	int k = 0;
	for (int i = 0; i < 256; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) {
		++a[mass[i] >> p & 255];
		if ((mass[i] >> p & 255) > 127) ++k;
	}
	for (int i = 1; i < 256; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[mass[i] >> p & 255]] = mass[i];
	for (int i = 0; i < k; ++i) mass[i] = b[n - k + i];
	for (int i = 0; i < n - k; ++i) mass[i + k] = b[i];
}

void Radix() {
	p = 0;
	for (int i = 0; i < 3; ++i) {
		RadixSort();
		p += 8;
	}
	RadixSort1();
}

void RadixMain(ofstream& fout) {
	//for (int i = 0; i < n; ++i) massr[i][0] = rand() % 10000000 - 20000;
	std::random_device rnd;    
	std::mt19937 rng(rnd());    
	std::uniform_int_distribution<int> uni(-2147483647, 2147483647); 
	for (int i = 0; i < n; ++i) mass[i] = uni(rng);
	auto begin = std::chrono::high_resolution_clock::now();
	Radix();
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	//for (int i = 0; i < n; ++i) cout << mass[i] << " ";
	//cout << endl << time.count() << endl;
	stime += time.count();
	fout << "," << time.count();
}
//Radix 1-байтовый на одномерном массиве

/*void RadixSort() {
	int a[256];
	for (int i = 0; i < 256; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) ++a[massr[i][1]];
	for (int i = 1; i < 256; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[massr[i][1]]] = massr[i][0];
	for (int i = 0; i < n; ++i) massr[i][0] = b[i];
}

void RadixSort1() {
	int a[256];
	int k = 0;
	for (int i = 0; i < 256; ++i) a[i] = 0;
	for (int i = 0; i < n; ++i) {
		++a[massr[i][1]];
		if (massr[i][1] > 127) ++k;
	}
	for (int i = 1; i < 256; ++i) a[i] += a[i - 1];
	int b[100000];
	for (int i = n - 1; i >= 0; --i) b[--a[massr[i][1]]] = massr[i][0];
	for (int i = 0; i < k; ++i) massr[i][0] = b[n - k + i];
	for (int i = 0; i < n - k; ++i) massr[i + k][0] = b[i];
}

void Radix() {
	int p = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < n; ++j) massr[j][1] = massr[j][0] >> p & 255;
		p += 8;
		RadixSort();
	}
	for (int j = 0; j < n; ++j) massr[j][1] = massr[j][0] >> 24 & 255;
	RadixSort1();
}

void RadixMain(ofstream &fout) {
	for (int i = 0; i < n; ++i) massr[i][0] = rand() % 10000000 - 20000;
	auto begin = std::chrono::high_resolution_clock::now();
	Radix();
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	//for (int i = 0; i < n; ++i) cout << massr[i][0] << " ";
	//cout << endl << time.count() << endl;
	stime += time.count();
	fout << "," << time.count();
}*/
//Radix на двумерном массиве

int comp1(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

void BuiltInSorting(ofstream& fout) {
	//for (int i = 0; i < n; ++i) mass[i] = rand() % 10000000 - 20000;
	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<int> uni(-2147483647, 2147483647);
	for (int i = 0; i < n; ++i) mass[i] = uni(rng);
	auto begin = std::chrono::high_resolution_clock::now();
	sort(mass.begin(), mass.end());         //вектор
	//qsort(mass, n, sizeof(int), comp1);
	//массив
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	//for (int i = 0; i < n; ++i) cout << mass[i] << " ";
	//cout << endl << time.count() << endl;
	stime += time.count();
	//fout << "," << time.count();
}

int main() {
	ofstream fout;
	fout.open("Sorting.txt");
	n = 25;
	fout << "\n" << "\n";
	for (int i = 0; i < 20; ++i) {
		cout << i;
		fout << "," << "," << n;
		stime = 0;
		for (int j = 0; j < 7; ++j) {
			mass.resize(n);
			//MergeMain(fout);
		}
		fout << "," << stime / 7 << ",";
		stime = 0;
		for (int j = 0; j < 7; ++j) {
			mass.resize(n);
			//RadixMain(fout);
		}
		fout << "," << stime / 7 << ",";
		stime = 0;
		for (int j = 0; j < 7; ++j) {
			mass.resize(n);
			BuiltInSorting(fout);
		}
		fout << "," << stime / 7 << "\n";
		//n += 100;
		n += 70;
		n *= 3;
		n /= 2;
	}
	fout.close();
}
