#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"


int main(int argc, char* argv[])
{
    if(argc != 9)
    {
        std::cerr << "Cantidad de parametros erronea";
        return 1;
    }
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

    int pca;
    int k = 5; // TODO variar
    int alfa = 5; // TODO variar
    baseDeDatos baseEntrenamiento = cargarBD(trainSet);
    if (method == 1)
    {
        pca = 0;
    }
    else
    {
        pca = 1;
    }

    vector<vector<pair<int, int> > > vectorDeVectores = k_fold(baseEntrenamiento, k, pca, alfa);

    std::vector<pair <int, int> > receivedAndExpected;


    for (int i = 0; i < vectorDeVectores.size(); ++i)
    {
        for (int j = 0; j < vectorDeVectores[i].size(); ++j)
        {
            receivedAndExpected.push_back(vectorDeVectores[i][j]);
        }
    }
    bool a = true;
    return 0;
}