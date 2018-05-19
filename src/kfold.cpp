#include "kfold.h"
#include "imagen.h"
//#include <cstdlib>
#include "pca.h"
#include "knn.h"

int cantClases = 41;
int imgPorClase = 10;

using namespace std;

//TODO:
//	1) Definir el k (radio) que vamos a usar. Lo pasamos por input?
//	2) Definir como pasar el k de k_fold

vector<vector<pair<int, int>>> k_fold(baseDeDatos bd, int k, int pca, int alfa){
	int imgATestearPorClase = imgPorClase/k;//La cantidad de folds. Ej. 2 fold nos da 5.
	int cantImagATestear = (imgPorClase/k)*cantClases;
	vector<vector<pair<int, int>> > resultado (imgATestearPorClase, vector<pair<int, int>>(cantImagATestear));

	int i(0);
	int j1(0);
	int j2(0);
	while(i < imgATestearPorClase){ // imgATestearPorClase también es la cantidad de folds que hacemos
		std::vector<int> vectorAux (k,0);
		while(j1 < k){
			vectorAux[j1] = j2;
			j2++; //j2 debería llegar hasta 10 en este caso. imgPorClase
			j1++;
		}
		resultado[i] = iFold(bd, vectorAux, pca, alfa);
		i++;
	}
}

//Los indices que recibe iFold son qué imagenes de las 10 vamos a tomar para testear.
vector<pair<int, int>> iFold(baseDeDatos bd, vector<int> indices, int pca, int alfa	){

	int cantidad_imagenes_test = indices.size()*cantClases;
	baseDeDatos trainingBase = {};//Para construir base de datos para testear.
	//Aca van a estar las imagenes que vamos a usar para testear. 
 	baseDeDatos imagenesTest{};

	//int k = 1;
	int i = 0;
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
	
	i = 0;
	//Armo vector resultado vacío. En cada índice va el resultado de evaluar cada una de las imagenes a testear
	std::vector<pair<int,int>> resultado(imagenesTest.size());
	int k = 20;//Para que funcione. Definir cual usamos y COMO
	if(pca == 1){
		while(i < imagenesTest.size()){
			resultado[i].first = bd[i].getId();

			int filas, columnas;
			filas = bd.size();
		    columnas=bd[0].getWidth()*bd[0].getHeight();

		    doubleMatrix matrizCaracteristicaMuestra(filas, doubleVector(alfa));
		    doubleMatrix cambioDeBaseTras (alfa, doubleVector(columnas));
    		doubleVector media (columnas);

			// doubleMatrix cambioDeBaseTras();
			// doubleVector media();
			// doubleMatrix matrizCaracteristicaMuestra();
			PCA(trainingBase, cambioDeBaseTras, media, matrizCaracteristicaMuestra, alfa);

		    doubleVector imagenNormalizada(columnas);
		    imagenNormalizada = ucharToDoubleVector (imagenesTest[i].getData(), columnas);

			imagenNormalizada = normalizarImagen(imagenNormalizada, media, cambioDeBaseTras, matrizCaracteristicaMuestra);
			resultado[i].second = modaPCA(k, matrizCaracteristicaMuestra, imagenNormalizada, bd);//PCA+KNN
			i++;
		}
	}
	if(pca == 0){//Solo KNN
		while(i <= imagenesTest.size()){
			resultado[i].first = bd[i].getId();
			resultado[i].second = moda(k, trainingBase, imagenesTest[i]);
			i++;
		}
	}
	//Y con esto ya estaría
	return resultado;
}

bool apareceEn(Imagen img, vector<int> indices){
	int i = 0;
	while(i < indices.size()){
		if(img.getName() == indices[i]){
			return true;
			i++;
		}
	}
	return false;
}






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
