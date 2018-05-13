#ifndef _KNN_H_
#define _KNN_H_


#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <queue>
#include <cmath>


using namespace std;

typedef priority_queue<double, int> colaKcercanos;

double distanciaEuclidea(const doubleVector &v1, const doubleVector &v2);
vector<int> k_cercanos(int k, baseDeDatos &matEntrenamiento, Imagen &imagenAEvaluar);
int moda(int k, baseDeDatos &matEntrenamiento, Imagen &imagen);


#endif
