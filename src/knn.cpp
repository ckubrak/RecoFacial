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

double distanciaEuclidea(Imagen &imag1, Imagen &imag2) {
	double distancia = 0;
	int tam = imag1.getHeight()*imag1.getWidth();//Asumo que las dos imagenes son del mismo tamaño
	int i = 0;
	double x;
	int y;
	for(i = 0; i < tam; i++){
		x = imag2.getData()[i] - imag1.getData()[i];
		distancia += x*x;
	}
	//Ganaríamos algo sacando la raiz?
	return sqrt(distancia);
}

vector<int> k_cercanosSort(int k, baseDeDatos &matEntrenamiento, Imagen &imagenAEvaluar){

	int i = 0;
	int j = 0;
	double distancia = 0;
	std::pair<double,int> indiceDistancia;
    std::vector<std::pair<double,int>> vectorKCercanos (k);
    std::vector<int> k_vecinos_cercanos (k);//RESULTADO
	
	int tamMatEntrenamiento = 0;
	tamMatEntrenamiento =  matEntrenamiento.size();

	while(i < tamMatEntrenamiento){
		distancia = distanciaEuclidea(matEntrenamiento[i], imagenAEvaluar);
		indiceDistancia.first = distancia;
		indiceDistancia.second = matEntrenamiento[i].getId();
		vectorKCercanos[i] = indiceDistancia;
		i++;
	}

	std::sort (std::begin(vectorKCercanos), std::end(vectorKCercanos));

	//Armo el vector que voy a devolver
	//std::vector<int> > k_vecinos_cercanos (k);//De longitud k, inicializado en ceros. 


	pair<double, int> pairAux;
	//Recorro lo que me quedó en la lista de prioridad y lo pongo en el vector. Agarro solo los indices. 
    for (int x = 0; x < k; x++){

	//while(x < 20){
		//int aux = vectorKCercanos[i].second;
		k_vecinos_cercanos[x] = vectorKCercanos[x].second;
		//k_vecinos_cercanos.push_back(aux);
	}

	return k_vecinos_cercanos;
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
	k_vecinos_cercanos = k_cercanosSort(k, matEntrenamiento, imagen);
	std::vector<int> vectorModa(cantClases, 0);
	int i = 0;
	int aux;
	while(i < k){
		aux = k_vecinos_cercanos[i];
		vectorModa[aux] ++;
		i++;
	}
	int result = *max_element(vectorModa.begin(), vectorModa.end());
    return result;
}

//PCA + KNN
double distanciaEuclideaPCA(doubleVector &imag1, doubleVector &imag2) {
	double distancia = 0;						
	int tam = imag1.size()*imag1.size();//Asumo que las dos imagenes son del mismo tamaño
	int i = 0;
	double x;
	int y;
	for(i = 0; i < tam; i++){
		x = imag2[i] - imag2[i];
		distancia += x*x;
	}
	//Ganaríamos algo sacando la raiz?
	return sqrt(distancia);
}

//Esta función me dice dada una base de datos cuantas imagenes tengo de cada sujeto. 
/*int cantidadId(baseDeDatos &baseDeDatos){
	//
	int tam = baseDeDatos.size();
	int i = 1;
	int aux = baseDeDatos[0].getId();
	int cantidadId = 1;
	while(i < tam){
		if(baseDeDatos[i].getId() == aux){
			cantidadId++;
		}
		i++;
	}
}
*/
vector<int> k_cercanosPCA(int k, doubleMatrix &matEntrenamiento, doubleVector &imagenAEvaluar, baseDeDatos &baseSinTransformar){

	int i = 0;
	//int j =  cantidadId(baseSinTransformar) - 1;

	double distancia = 0;

	std::pair<double,int> indiceDistancia;
    std::priority_queue<std::pair<double,int>> colaKcercanos;

	int tamMatEntrenamiento = 0;
	tamMatEntrenamiento =  matEntrenamiento.size();
	while(i < tamMatEntrenamiento){
		distancia = distanciaEuclideaPCA(matEntrenamiento[i], imagenAEvaluar);
		indiceDistancia.first = distancia;
		indiceDistancia.second = baseSinTransformar[i].getId();//el "id" de esa imagen
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
		k_vecinos_cercanos[aux] = pairAux.second;
		colaKcercanos.pop();
		aux++;
	}

	return k_vecinos_cercanos;
}

vector<int> k_cercanosPCASort(int k, doubleMatrix &matEntrenamiento, doubleVector &imagenAEvaluar, baseDeDatos &baseSinTransformar){

	int i = 0;

	double distancia = 0;
	std::pair<double,int> indiceDistancia;
    std::vector<std::pair<double,int>> vectorKCercanos;

	int tamMatEntrenamiento = 0;
	tamMatEntrenamiento =  matEntrenamiento.size();

	while(i < tamMatEntrenamiento){
		distancia = distanciaEuclideaPCA(matEntrenamiento[i], imagenAEvaluar);
		indiceDistancia.first = distancia;
		indiceDistancia.second = baseSinTransformar[i].getId();
		vectorKCercanos[i] = indiceDistancia;
		i++;
	}
	std::sort (std::begin(vectorKCercanos), std::end(vectorKCercanos));

	//Armo el vector que voy a devolver
	std::vector<int> k_vecinos_cercanos(k, 0);//De longitud k, inicializado en ceros. 
	i = 0;
	pair<double, int> pairAux;
	//Recorro lo que me quedó en la lista de prioridad y lo pongo en el vector. Agarro solo los indices. 
	while(i < k){
		k_vecinos_cercanos[i] = vectorKCercanos[i].second;
		i++;
	}
	return k_vecinos_cercanos;
}



int modaPCA(int k, doubleMatrix &matEntrenamiento, doubleVector &imagen, baseDeDatos &baseSinTransformar){
	std::vector<int> k_vecinos_cercanos(k, 0);
	k_vecinos_cercanos = k_cercanosPCA(k, matEntrenamiento, imagen, baseSinTransformar);
	std::vector<int> vectorModa(cantClases, 0);
	int i = 0;
	int aux;
	while(i < k){
		aux = k_vecinos_cercanos[i];
		vectorModa[aux] ++;
		i++;
	}
	int result = *max_element(vectorModa.begin(), vectorModa.end());
    return result;
}
