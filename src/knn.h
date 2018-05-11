#ifndef _KNN_H_
#define _KNN_H_


#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <queue>


using namespace std;

typedef priority_queue<double, int> colaKcercanos;

int distanciaEuclidea(const imagen &im1, const imagen &im2) const;
vector<int> k_cercanos(int k, doubleMatrix &matEntrenamiento, doubleVector &imagen);

#endif
