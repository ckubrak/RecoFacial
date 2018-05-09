#ifndef _KNN_H_
#define _KNN_H_


#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <queue>


using namespace std;

typedef vector<int> imagen;
//Esto es el resultado. Vector con la distancia en el double y la clase en el int.
//typedef vector<pair<double, int>> knn_res;
//O si no lo guardamos en un vector<int>, no necesitamos la distancia. 

typedef priority_queue<double, int> colaKcercanos;



class knn {
public:
	//Los valores de las clases deben estar en el rango [0, cantidadDeClases).
	knn(int k, const vector<imagen> &imagenes, const vector<int> &clasesPorElemento, int cantClases);
	~Knn();
	int clasificarElemento(const imagen &imagen) const;
	vector<tipoDistanciaIndiceElemento> obtenerDistanciasCuadradasConElemento(const imageon &imagen)const;
	int distanciaEuclidea(const imagen &im1, const imagen &im2)const;
	vector<int> obtenerIndicesDeKElementosMasCercanos(const vector<tipoDistanciaIndiceElemento> &distanciasConIndices) const;
	int obtenerClaseDeElementoConMayorFrecuencia(const vector<int> &indicesDeElementos)const;
private:
	int _k;
	vector<imagen> _imagenes;
	vector<int> _clasesPorElemento;
	int _cantClases;
};

#endif
