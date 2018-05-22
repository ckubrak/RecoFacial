#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"
// #include "misc.h"

int main_kfold()
{
    int method;
    std::string trainSet = "../tests/testRed.in";

    int pca = 0;
    int k = 5; // TODO variar
    int alfa = 5; // TODO variar

    baseDeDatos baseEntrenamiento = cargarBD(trainSet);

    vector<vector<pair<int, int> > > vectorDeVectores = k_fold(baseEntrenamiento, k, pca, alfa);

    std::vector<int> truePos; 
    std::vector<int> trueNeg;
    std::vector<int> falsePos;
    std::vector<int> falseNeg;

    std::vector<pair <int, int> > receivedAndExpected;
    for (int i = 0; i<vectorDeVectores.size(); i++)
    {
        for (int j=0; i<vectorDeVectores[i].size();i++)
        {
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

        truePos.push_back(tPos);
        trueNeg.push_back(tNeg);
        falsePos.push_back(fPos);
        falseNeg.push_back(fNeg);
    }


    return 0;
}