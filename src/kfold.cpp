#include "kfold.h"
#include "image.h"
#include <cstdlib>
#include "pca.h"
#include "knn.h"
#include "imagen.h"

const int cantClases(41);
const int imgPorClase(10);


// bool estaRepetido(vector<int> &fila, int elemento){
// 	int n(fila.size());
// 	int i(0);
// 	while(i < n){
// 		if(fila[i] == elemento){
// 			return true;
// 		}
// 	i++;
// 	}
// 	return false;
// }

vector<vector<int, int>> k_fold3(baseDeDatos bd, int k){
	std::vector<vector<pair(int,int)>> result ();
	int imgATestearPorClase = imgPorClase/k;//La cantidad de folds. Ej. 2 fold nos da 5.
	int cantImagATestear = (imgPorClase/k)*cantClases;
	vector<vector<pair<int, int>> > resultado (imgATestearPorClase, vector<pair<int, int>>(cantImagATestear));

	int i(1);
	int j1(1);
	int j2(1);
	while(i < imgATestearPorClase){ // imgATestearPorClase también es la cantidad de folds que hacemos
		std::vector<int> vectorAux (k,0);
		while(j1 < k){
			vectorAux[j1] = j2;
			j2++; //j2 debería llegar hasta 10 en este caso. imgPorClase
			j1++;
		}
		resultado[i] = iFold(baseDeDatos, vectorAux);
		i++;
	}
}
//Los indices que recibe iFold son qué imagenes de las 10 vamos a tomar para testear.
vector<pair<int, int>> iFold(baseDeDatos bd, vector<int> indices){

	int cantidad_imagenes_test = indices.size()*cantClases;
	baseDeDatos trainingBase = {};//Para construir base de datos para testear.
	//Aca van a estar las imagenes que vamos a usar para testear. 
 	baseDeDatos imagenesTest{};

	int indiceImagen = 1;
	int indiceClase = 1;
	int k = 1;
	int i = 1;
	int cantImagenesTotales = cantClases*imgPorClase;//en este caso 41*10
	while(i < cantImagenesTotales){
		if(!apareceEn(bd[i], indices)){
			trainingBase.push_back(bd[i]);
		}else{
			imagenesTest.push_back(bd[i]);
		}
	i++;
	}//Listo, ahora tendríamos la matriz de entrenamiento que queremos.
	//Acá ya estaríamos listos para llamar a knn y pca.


}

bool apareceEn(Imagen img, vector<int> indices){
	int i = 1;
	while(i < indices.size()){
		if(img.getName() == indices[i]){
			return true;
		}
	}
	return false;
}

// void k_fold2(baseDeDatos bd, int k, float tfold){
// 	std::vector<int> folds(cantClases, 0);
// 	int random;
// 	int imagenes_a_testear = tfold*imgPorClase;
// 	//assert(imagenes_a_testear%10 == 0). Es decir que tomemos folds multiplos de 41
// 	//para poder sacar una imagen de cada uno. 

// 	baseDeDatos trainingBase = {};//Creo una base de entrenamiento vacia

// 	//Aca creo una matriz de 41 filas, cada una con columnas de k elementos.
// 	//Es decir, guardo cuales k imagenes voy a agarrar de cada sujeto. 
// 	vector<vector<int>> matriz_folds(cantClases, vector<int>(imagenes_a_testear));

// 	int i(0);
// 	int j(0);
// 	int xfold(1); //Por cual fold vamos.

// 	while(i < cantClases){
// 		while(j < imagenes_a_testear){
// 		do{
// 		random = rand() % imgPorClase + 1;
// 		}
// 		while(estaRepetido(matriz_folds[i], random));
// 		matriz_folds[i][j] = random; 
// 		j++;
// 		}
// 	j = 0;
// 	i++;
// 	}
// 	//Ahora tengo en matriz_folds las imagenes que vamos a testear de cada sujeto
// 	i = 0;
// 	while(i < cantClases){
// 		while(j < imgPorClase){
// 			if(!estaRepetido(matriz_folds[i], j+1)){
// 				trainingBase.push_back(bd[i*imgPorClase+j]);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}

// }
