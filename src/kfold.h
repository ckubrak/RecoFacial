#ifndef _KFOLD_H_
#define _KFOLD_H_

#include <vector>
#include <math.h>       /* sqrt */
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> //randonm
#include "pca.h"

//void k_fold( baseDeDatos bd, int k, float tfold, int cmuestras, int cclases);
//void k_fold2(baseDeDatos bd, int k, float tfold);
//bool estaRepetido(vector<int> &fila, int elemento);
vector<vector<int, int>> k_fold(baseDeDatos bd, int k, int pca, int alfa);
vector<pair<int, int>> iFold(baseDeDatos bd, vector<int> indices, int pca, int alfa);
bool apareceEn(Imagen img, vector<int> indices)

#endif
