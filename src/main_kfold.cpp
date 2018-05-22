#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"
// #include "misc.h"

int main_kfold()
{
    int method;
    std::string trainSet = "/home/sly/Documents/Metnum/TP2-IMAGENES/tests/testFullRed.in";

    int pca = 0;
    int k = 5; // TODO variar
    int alfa = 5; // TODO variar

    baseDeDatos baseEntrenamiento = cargarBD(trainSet);
    std::cout << "Size: " << baseEntrenamiento.size() << std::endl;

    vector<vector<pair<int, int> > > vectorDeVectores = k_fold(baseEntrenamiento, k, pca, alfa);
    std::cout << "Size vectorDeVectores: " << vectorDeVectores.size() << std::endl;
    
    std::vector<int> truePos; 
    std::vector<int> trueNeg;
    std::vector<int> falsePos;
    std::vector<int> falseNeg;

    std::vector<pair <int, int> > receivedAndExpected;
    for (int i = 0; i<vectorDeVectores.size(); i++)
    {
        std::cout << "Size vectorDeVectores en : "<< i<< " " << vectorDeVectores[i].size() << std::endl; 
        for (int j=0; j<vectorDeVectores[j].size();j++)
        {
            // std::cout << "j = " << j<<std::endl;
            receivedAndExpected.push_back(vectorDeVectores[i][j]);
        }
    }

    for (int id = 1; id< vectorDeVectores.size()+1; id++) 
    {
    int tPos = 0; 
    int tNeg = 0; 
    int fPos = 0; 
    int fNeg = 0; 
        if(id == receivedAndExpected[id-1].first)
        {
            if (receivedAndExpected[id-1].first == receivedAndExpected[id-1].second)
            {
                tPos++;
            }
            else
            {
                fNeg++;
            }

        }
        else
        {
            if (receivedAndExpected[id-1].first == receivedAndExpected[id-1].second)
            {
                fPos++;
            }
            else
            {
                tNeg++;
            }
        }
        std::cout << tPos << tNeg << fPos << fNeg << std::endl;
        truePos.push_back(tPos);
        trueNeg.push_back(tNeg);
        falsePos.push_back(fPos);
        falseNeg.push_back(fNeg);
    }


    return 0;
}