#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"
#include "misc.h"

int main(int argc, char* argv[])
{
    int method;
    std::string trainSet, testSet, results;
    for (int i = 1; i < argc; ++i)
    {

        std::cout <<argv[i] <<std::endl;
        std::string toParse = argv[i];
        if (toParse == "-m")
        {
            std::cout << "m";
            method = atoi(argv[i+1]);
        }
        else if (toParse == "-i") 
        {
            trainSet = argv[i+1];
        }
        else if (toParse == "-q")
        {
            testSet = argv[i+1];
        }
         else if (toParse == "-o")
        {
            results = argv[i+1];
        }

    }

    int result;
    int k = 5; // TODO variar
    int alfa = 5; // TODO variar
    baseDeDatos baseEntrenamiento = cargarBD(testSet);
    std::ifstream input(testSet);
    std::string imagen;
    std::string line;

    int lePegamos = 0;
    int totalImgs = 0;
    std::vector<std::vector<int> > vectordeKCercanos;


		    int filas, columnas;
		    filas = baseEntrenamiento.size();
	        columnas=baseEntrenamiento[0].getWidth()*baseEntrenamiento[0].getHeight();

		    doubleMatrix matrizCaracteristicaMuestra(baseEntrenamiento.size(), doubleVector(alfa));
	        doubleMatrix cambioDeBaseTras (alfa, doubleVector(columnas));
		    doubleVector media (columnas);
    if (method == 1)
    {
            PCA (baseEntrenamiento, cambioDeBaseTras, media, matrizCaracteristicaMuestra, alfa);
    }
    while (std::getline(input, line))
    {



        std::size_t found = line.find_first_of(", ");      //primer delimitador
        imagen = line.substr(0, found);
 
        line = line.substr(found, line.size()-1);

        std::size_t inicio = line.find_first_not_of(", "); //inicio de datos significativos
        line = line.substr(inicio, line.size()-1);
        int id = std::stoi (line);
        Imagen nuevaImagen(imagen,-1);
 
        if (method == 0)
        {
            result = moda(k, baseEntrenamiento, nuevaImagen);

        }
       else 
        {

            doubleVector imagenVector = ucharToDoubleVector (nuevaImagen.getData(), columnas);
            result = modaPCA(k, matrizCaracteristicaMuestra, imagenVector, baseEntrenamiento);
            // result = moda(k, baseEntrenamiento, nuevaImagen);
        }

        totalImgs++;
        std::cout << id << " " << result<<std::endl;
        if (id == result)
        {
            lePegamos++;
            std::cout << "Le pegamos " << lePegamos << std::endl;
            std::cout << "Total " << totalImgs << std::endl;
        }

        ofstream fileOUT(results, ios::app);
        fileOUT << imagen <<", " << result << "," << endl;
        fileOUT.close(); 

    }

    std::cout << "Paramtros";
    ofstream parametros("parametros.txt", ios::app);
    parametros << "Correctas: " << lePegamos << " sobre: " << totalImgs << " => " << (double(lePegamos))/totalImgs<< std::endl;
    parametros << "Parametros usados: "<< std::endl;
    parametros << "k (kNN): " << k<<std::endl;
    if (method == 1)
        parametros << "alfa : " << alfa<<std::endl;

    parametros.close(); 
    return 0;

    // Para poder correr el k-fold
    // int pca = atoi(argv[1]);
    // int k = atoi(argv[2]);
    // int alfa = atoi(argv[3]);
    // int kknn = atoi(argv[4]);
    // return main_kfold(pca, k, alfa, kknn);
} 
