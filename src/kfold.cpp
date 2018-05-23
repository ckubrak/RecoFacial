#include "kfold.h"
#include "imagen.h"
//#include <cstdlib>
#include "pca.h"
#include "knn.h"

int cantClases;
int imgPorClase;

using namespace std;

//TODO:
//	1) Definir el k (radio) que vamos a usar. Lo pasamos por input?
//	2) Definir como pasar el k de k_fold

vector<vector<pair<int, int>>> k_fold(baseDeDatos bd, int k, int pca, int alfa){
	//Tendríamos que usar 5 fold. O sea, imagenesPorClase = 2.

	cantClases = cantidadClases(bd);
	imgPorClase = cantidadImagenesPorClase(bd);

	int cantImagATestear = (imgPorClase/k)*cantClases;
	vector<vector<pair<int, int>> > resultado (k, vector<pair<int, int>>(cantImagATestear));
	//Vector que en cada i contiene un vector con los subindices de qué elementos de cada clase vamos a usar
	//para testear.
	int i = 0;

	while(i < k){

		int cantImagATestearPorClase = imgPorClase/k;
		std::vector<std::vector<int>> vectorDeIndices;
		int j1 = 0;
		while(j1+1 < imgPorClase+1){
			std::vector<int> aux;
			for(int j2 = 0; j2 < cantImagATestearPorClase ; j2++){
				aux.push_back(j1+1);
				j1++;
			}
			vectorDeIndices.push_back(aux);
		}
		// std::vector<std::vector<int>>  vectorAux;
		// vectorAux.push_back({1});
		// vectorAux.push_back({2});
		// vectorAux.push_back({3});
		// vectorAux.push_back({4});
		// vectorAux.push_back({5});
		resultado[i] = (iFold(bd, vectorDeIndices[i], pca, alfa));

		std::cout << "Resultado en i = " << i<< " :";
		for (int j=0; j<resultado[i].size();j++)
		{

			std::cout << resultado[i][j].first <<" "<< resultado[i][j].second << std::endl;
			if (resultado[i][j].first != resultado[i][j].first )
				std::cout << "Aca dio maaaaaaaaaal"<<std::endl;
		}
		i++;
	}
	return resultado;
}

//Los indices que recibe iFold son qué imagenes de las 10 vamos a tomar para testear.
vector<pair<int, int>> iFold(baseDeDatos bd, vector<int> indices, int pca, int alfa	){

	cantClases = cantidadClases(bd);
	imgPorClase = cantidadImagenesPorClase(bd);

	int cantidad_imagenes_test = indices.size()*cantClases;
	baseDeDatos trainingBase = {};//Para construir base de datos para testear.
	//Aca van a estar las imagenes que vamos a usar para testear.
 	baseDeDatos imagenesTest{};

	//int k = 1;
	int i = 0;
	int cantImagenesTotales = cantClases * imgPorClase;//en este caso 41*10
	while(i < cantImagenesTotales){
		if(!apareceEn(bd[i], indices)){
			trainingBase.push_back(bd[i]);
		}else{
			imagenesTest.push_back(bd[i]);
		}
		//std::cout <<i << " ";
		i++;
	}//Listo, ahora tendríamos la matriz de entrenamiento que queremos.
	//Acá ya estaríamos listos para llamar a knn y pca.

	i = 0;
	//Armo vector resultado vacío. En cada índice va el resultado de evaluar cada una de las imagenes a testear
	std::vector<pair<int,int>> resultado(imagenesTest.size());
	int k = 20;//Para que funcione. Definir cual usamos y COMO
	if(pca == 1){

		int filas, columnas;
		filas = bd.size();
	    columnas=bd[0].getWidth()*bd[0].getHeight();

	    doubleMatrix matrizCaracteristicaMuestra(filas, doubleVector(alfa));
	    doubleMatrix cambioDeBaseTras (alfa, doubleVector(columnas));
		doubleVector media (columnas);

		PCA(trainingBase, cambioDeBaseTras, media, matrizCaracteristicaMuestra, alfa);

		while(i < imagenesTest.size()){
			resultado[i].first = imagenesTest[i].getId();//El id original, el que debería dar. 

		    doubleVector imagenNormalizada(columnas);
		    imagenNormalizada = ucharToDoubleVector (imagenesTest[i].getData(), columnas);

			imagenNormalizada = normalizarImagen(imagenNormalizada, media, cambioDeBaseTras, matrizCaracteristicaMuestra);
			resultado[i].second = modaPCA(k, matrizCaracteristicaMuestra, imagenNormalizada, bd);//PCA+KNN
			i++;
		}
	}
	if(pca == 0){//Solo KNN
		while(i < imagenesTest.size()){
			std::pair <int,int> parResultado;
			parResultado = std::make_pair (imagenesTest[i].getId(),moda(k,trainingBase,imagenesTest[i]));
			resultado[i] = parResultado;
			// resultado[i].first = bd[i].getId();//El resultado que debería dar
			// resultado[i].second = moda(k, trainingBase, imagenesTest[i]);//El resultado que dió nuestro algoritmo
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
// Se asume que todas las clases tienen la misma cantidad de imagenes, es decir que la base esta balanceada
int cantidadImagenesPorClase(baseDeDatos& bd)
{
  //recorro la bd contando los elementos que tienen igual id
  int tam=bd.size();
  int idanterior;
  int contador=0;
  if (tam > 0)
      idanterior = bd[0].getId();
  int i=0;
  while(i<tam && idanterior==bd[i].getId())
  {
    contador++;
    i++;
  }
  return contador;
}

//se asume todas las clases tienen la misma cantidad de imagenes
int cantidadClases(baseDeDatos& bd)
{
	if (bd.size()>0)
		return (bd.size()/cantidadImagenesPorClase(bd));
	else
		return 0;
}
