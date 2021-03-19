#include <stdio.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#define ARRAYSIZE 400000
using namespace std::chrono;
using namespace std;

double times, times2;
duration<double> interval;
high_resolution_clock::time_point start, end, start1, end2;

void cuadrado(int a[], int inc, int fin){
	for(int i = inc; i < fin; i++){
		a[i] = pow(i,2);
	}
}

int main(void){
	int array[ARRAYSIZE] = {};
	for(int i = 0; i<ARRAYSIZE; i++){
		array[i] = i;
	}
	auto start = high_resolution_clock::now();
	thread th1(cuadrado, array, 0, 400000);
	th1.join();
	auto end = high_resolution_clock::now();
	interval = duration_cast<duration<double>>(end - start);
	times = interval.count();

	auto start1 = high_resolution_clock::now();
	thread th2(cuadrado, array, 0, 99999);
	thread th3(cuadrado, array, 100000, 199999);
	thread th4(cuadrado, array, 200000, 299999);
	thread th5(cuadrado, array, 300000, 399999);
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	auto end1 = high_resolution_clock::now();
	interval = duration_cast<duration<double>>(end1-start1);
	times2 = interval.count();

	cout << "tiempo de ejecución a un hilo: " << times << endl;
	cout << "tiempo de ejecucíon a cuatro hilos: " << times2 << endl;

	return 0;
}
