#include "knn.h"
#include "pca.h"
#include <assert.h>
#include <algorithm>
#include <vector>
#include <cmath>


using namespace std;

// 1) Guardar el valor del primer pixel
// 2) Recorrer la matriz de entrenamiento
// 3) Calcular distancia euclidea entre la imagen a evaluar y la imagen i, 1<= i <= k
// 4) Guardar los K más valores más chicos. 


//Podriamos cambiar int a double para darle mas presicion
double distanciaEuclidea(const doubleVector &v1, const doubleVector &v2) const {
	//v1 y v2 de la misma dimension
	assert (v1.size() == v2.size());
	double distancia = 0;
	int tam = v1.size()
	int i = 0;
	double x;
	int y;
	for(i = 0; i < tam; i++){
		x = v1[i] - v2[i];
		distancia += x*x;
	}
	//Ganaríamos algo sacando la raiz?
	return sqrt(distancia);
}



vector<int> k_cercanos(int k, doubleMatrix &matEntrenamiento, doubleVector &imagen){

	int i = 0;
	double distancia = 0;
	pair<double, int> indiceDistancia;
	priority_queue<double, int> colaKcercanos;
	while(i< matEntrenamiento.size()){
		distancia = distanciaEuclidea(matEntrenamiento[i], imagen);
		indiceDistancia.first = distancia;
		indiceDistancia.second = i;//O i+1? Acá va la clase de la imagen

		colaKcercanos.push(indiceDistancia);//Agrego el pair a la cola. Deberían quedar ordenados por distancia

		i++;
	}

	//La cola de prioridad ordena de mayor a menor. Le saco los n-k de adelante y me quedan los k elementos más chicos.
	int aux = matEntrenamiento.size() - k;
	while(aux > 0){
		colaKcercanos.pop();
		aux-- ;
	}

	//Armo el vector que voy a devolver
	vector<int> k_vecinos_cercanos;
	aux = 0;
	pair<double, int> pairAux;
	//Recorro lo que me quedó en la lista de prioridad y lo pongo en el vector. Agarro solo los indices. 
	while(aux < k){
		pairAux = colaKcercanos.top();
		k_vecinos_cercanos[k-aux] = pairAux.second;
		colaKcercanos.pop();
		aux++;
	}

	return k_vecinos_cercanos;
}



int knn::moda(int k, doubleMatrix &matEntrenamiento, doubleVector &imagen){
	std::vector<int> k_vecinos_cercanos(k, 0);
	k_vecinos_cercanos = k_cercanos(k, matEntrenamiento, imagen);
	std::vector<int> vectorModa(41, 0);
	int i = 0;
	int aux;
	int result = 0;
	//En vector moda tengo cuantas veces el sujeto_i queda entre los k mas cercanos
	while(i < k){
		aux = k_vecinos_cercanos[i];
		vectorModa[i] ++;
		i++;
	}
    result = std::max_element(vectorModa.begin(), vectorModa.end());
    return result;
}