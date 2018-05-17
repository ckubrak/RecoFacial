#include "knn.h"
#include "pca.h"
#include "imagen.h"
#include <assert.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

const int cantClases (41); 

// 1) Guardar el valor del primer pixel
// 2) Recorrer la matriz de entrenamiento
// 3) Calcular distancia euclidea entre la imagen a evaluar y la imagen i, 1<= i <= k
// 4) Guardar los K mas valores mas chicos. 


//Podriamos cambiar int a double para darle mas presicion
double distanciaEuclidea(Imagen imag1, Imagen &imag2) {
	double distancia = 0;
	int tam = imag1.getHeight()*imag1.getWidth();//Asumo que las dos imagenes son del mismo tamaño
	int i = 0;
	double x;
	int y;
	for(i = 0; i < tam; i++){
		x = imag2.getData()[i] - imag2.getData()[i];
		distancia += x*x;
	}
	//Ganaríamos algo sacando la raiz?
	return sqrt(distancia);
}



vector<int> k_cercanos(int k, baseDeDatos &matEntrenamiento, Imagen &imagenAEvaluar){

	int i = 0;
	int j = 0;
	double distancia = 0;
	std::pair<double,int> indiceDistancia;
    std::priority_queue<std::pair<double,int>> colaKcercanos;
	int tamMatEntrenamiento = 0;
	tamMatEntrenamiento =  matEntrenamiento.size();

	while(i < tamMatEntrenamiento){
		distancia = distanciaEuclidea(matEntrenamiento[i], imagenAEvaluar);
		indiceDistancia.first = distancia;
		indiceDistancia.second = matEntrenamiento[i].getId();
		colaKcercanos.push(indiceDistancia);//Agrego el pair a la cola. Deberían quedar ordenados por distancia
		i++;
	}

	//La cola de prioridad ordena de mayor a menor. Le saco los n-k de adelante y me quedan los k elementos más chicos.
	int aux = tamMatEntrenamiento - k;
	while(aux > 0){
		colaKcercanos.pop();
		aux-- ;
	}

	//Armo el vector que voy a devolver
	std::vector<int> k_vecinos_cercanos(k, 0);//De longitud k, inicializado en ceros. 
	aux = 0;
	pair<double, int> pairAux;
	//Recorro lo que me quedó en la lista de prioridad y lo pongo en el vector. Agarro solo los indices. 
	while(aux < k){
		pairAux = colaKcercanos.top();//Accedo al tope de la cola
		k_vecinos_cercanos[k-aux] = pairAux.second;
		colaKcercanos.pop();
		aux++;
	}

	return k_vecinos_cercanos;
}



int moda(int k, baseDeDatos &matEntrenamiento, Imagen &imagen){
	std::vector<int> k_vecinos_cercanos(k, 0);
	k_vecinos_cercanos = k_cercanos(k, matEntrenamiento, imagen);
	std::vector<int> vectorModa(cantClases, 0);
	int i = 0;
	int aux;
	while(i < k){
		aux = k_vecinos_cercanos[i];
		vectorModa[i] ++;
		i++;
	}
	int result = *max_element(vectorModa.begin(), vectorModa.end());
    return result;
}