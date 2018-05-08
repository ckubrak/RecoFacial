#include "kfold.h"
#include "image.h"

void k_fold(baseDeDatos bd, int k, float tfold, int cmuestras, int cclases){
	//k: cantidad de folds
	//tfold: tamaño del fold en porcentaje, por ejemplo 0.2
	//cmuestras: cantidad de muestras por cada clase
	//cclases: cantidad de clases
	int cantfold = cmuestras/tfold;
	for(int i = 0; i < k; i++){
		baseDeDatos training = {};
		baseDeDatos test = {};
		for(int j = 0; j < cclases; j++){
			for(int l = 0; l < cmuestras; l++){
				if(((cant*k) != l) && ((cant*k+1) != l)){
					training.push_back(bd[j*cmuestras+l]);
				}else{
					test.push_back(bd[j*cmuestras+l]);
				}
			}
		}
		//hacer entrenamiento y testeo
	}
}
