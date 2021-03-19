#include <stdio.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#define ARRAYSIZE 400000   //declaraciòn del tamaño del array
using namespace std::chrono;
using namespace std;

double times, times2;     //declaraciòn de las variables que almacenan los resultados de los tiempos
duration<double> interval;
high_resolution_clock::time_point start, end, start1, end2; // declaraciòn de las banderas temporales que se van a usar para calcular el tiempo de ejecuciòn

void cuadrado(int a[], int inc, int fin){ //funciòn que calcula el cuadrado de los nùmeros pertenecienes a una secciòn de un array no retorna nada
	for(int i = inc; i < fin; i++){
		a[i] = pow(i,2);     //se encarga de reescribir el array con los nuevos numeros al cuadrado 
	}
}

int main(void){
	int array[ARRAYSIZE] = {};  //pone todos los elementos del array en ceros
	for(int i = 0; i<ARRAYSIZE; i++){    //se encarga de crear un array con nùmeros desde el 0 hasta el 399999
		array[i] = i;
	}
	auto start = high_resolution_clock::now();  //bandera de inicio del primer cronometro
	thread th1(cuadrado, array, 0, 400000);   //uso del primer hilo
	th1.join();
	auto end = high_resolution_clock::now();//bandera de final del cronometro
	interval = duration_cast<duration<double>>(end - start);//calculo del tiempo de ejecuciòn
	times = interval.count();

	auto start1 = high_resolution_clock::now();
	thread th2(cuadrado, array, 0, 99999);       //uso de los 4 hilos con secciones iguales del array
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

	cout << "tiempo de ejecución a un hilo: " << times << endl;//resultados de la ejecuciòn del programa
	cout << "tiempo de ejecucíon a cuatro hilos: " << times2 << endl;

	return 0;
}
