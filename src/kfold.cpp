#include "kfold.h"
#include "imagen.h"
//#include <cstdlib>
#include "pca.h"
#include "knn.h"

int cantClases = 41;
int imgPorClase = 5;

using namespace std;

//TODO:
//	1) Definir el k (radio) que vamos a usar. Lo pasamos por input?
//	2) Definir como pasar el k de k_fold

vector<vector<pair<int, int>>> k_fold(baseDeDatos bd, int k, int pca, int alfa){
	int imgATestearPorClase = imgPorClase/k;//La cantidad de folds. Ej. 2 fold nos da 5.
	//Tendríamos que usar 5 fold. O sea, imagenesPorClase = 2.
	int cantImagATestear = (imgPorClase/k)*cantClases;
	vector<vector<pair<int, int>> > resultado (k, vector<pair<int, int>>(cantImagATestear));
	//O sea, un vector que en cada i contiene un vector con los subindices de qué elementos de cada clase vamos a usar
	//para testear.
	int i(0);
	int j1(0);
	int j2(1);

	while(i < k){ // imgATestearPorClase también es la cantidad de folds que hacemos
		//std::vector<int> vectorAux (imgATestearPorClase,0);
		// int x = 1;//Creo que esto crearia todos los folds iguales
		// while (x*i < imgATestearPorClase*i)
		// {
		// 	vectorAux[x] = x;
		// 	x++;
		// }
		// while(j1 < imgATestearPorClase){
		// 	vectorAux[j1] = j2;
		// 	j2++; //j2 debería llegar hasta 10 en este caso. imgPorClase
		// 	j1++;
		// }
		//std::cout << "Vector aux " << vectorAux.size() << std::endl;
		//std::vector<std::vector<int>> vectorAux;
		std::vector<std::vector<int>>  vectorAux;
		vectorAux.push_back({1, 2});
		vectorAux.push_back({3, 4});
		vectorAux.push_back({5, 6});
		vectorAux.push_back({7, 8});
		vectorAux.push_back({9, 10});


		resultado[i] = iFold(bd, vectorAux[i], pca, alfa);
		i++;
	}
	return resultado;
}

//Los indices que recibe iFold son qué imagenes de las 10 vamos a tomar para testear.
vector<pair<int, int>> iFold(baseDeDatos bd, vector<int> indices, int pca, int alfa	){

	int cantidad_imagenes_test = indices.size()*cantClases;
	baseDeDatos trainingBase = {};//Para construir base de datos para testear.
	//Aca van a estar las imagenes que vamos a usar para testear. 
 	baseDeDatos imagenesTest{};

	//int k = 1;
	int i = 0;
	int cantImagenesTotales = cantClases * 10;//en este caso 41*10
	while(i < cantImagenesTotales){
		if(!apareceEn(bd[i], indices)){
			trainingBase.push_back(bd[i]);
		}else{
			imagenesTest.push_back(bd[i]);
		}
		std::cout <<i << " ";
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
		while(i < imagenesTest.size()){
			resultado[i].first = bd[i].getId();//El resultado que debería dar
			resultado[i].second = moda(k, trainingBase, imagenesTest[i]);//El resultado que dió nuestro algoritmo
			// std::cout << "Valor de i: " << i << std::endl;
			// std::cout << "Size: " << imagenesTest.size() << std::endl;
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
		}
		i++;
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
