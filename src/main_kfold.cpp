#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"

double presicion(int truePos, int falsePos)
{
    return double(truePos/(truePos + falsePos));
}
double recall(int truePos, int falseNeg)
{
    return double(truePos/(truePos + falseNeg));
}

double accuracy(int truePos, int trueNeg, int falsePos, int falseNeg)
{
    return double(truePos + trueNeg /(truePos + trueNeg + falsePos + falseNeg));
}
double mediaArmonica(double presicion, double recall)
{
    return 2 * (presicion*recall/presicion + recall);
}
int main_kfold()
{
    int method;
    std::string trainSet = "../tests/testFullRed.in";

    int pca = 1;
    int k = 5; // TODO variar
    int alfa = 5; // TODO variar

    baseDeDatos baseEntrenamiento = cargarBD(trainSet);
    std::cout << "Size: " << baseEntrenamiento.size() << std::endl;

    vector<vector<pair<int, int> > > vectorDeFolds = k_fold(baseEntrenamiento, k, pca, alfa);

    for (int fold = 0; fold < vectorDeFolds.size(); fold++ )
    {
        for (int i = 0; i < vectorDeFolds[fold].size(); i++)
        {

        }
    }
    // std::cout << "Size vectorDeVectores: " << vectorDeVectores.size() << std::endl;
    
    // std::vector<double> presicions; 
    // std::vector<double> recalls;
    // std::vector<double> accuracys;
    // std::vector<double> mediaArmonicas;

    // std::vector<pair <int, int> > receivedAndExpected;
    // for (int i = 0; i<vectorDeVectores.size(); i++)
    // {
    //     std::cout << "Size vectorDeVectores en : "<< i<< " " << vectorDeVectores[i].size() << std::endl; 
    //     for (int j=0; j<vectorDeVectores[j].size();j++)
    //     {
    //         // std::cout << "j = " << j<<std::endl;
    //         // std::cout << vectorDeVectores[i][j].first << " " << vectorDeVectores[i][j].second << std::endl;
    //         receivedAndExpected.push_back(vectorDeVectores[i][j]);
    //     }
    // }
    // std::cout << "uaeonts" <<receivedAndExpected.size() << std::endl;

    // for (int id = 1; id< vectorDeVectores.size()+1; id++) 
    // {
    // int tPos = 0; 
    // int tNeg = 0; 
    // int fPos = 0; 
    // int fNeg = 0; 
    //     if(id == receivedAndExpected[id-1].first)
    //     {
    //         if (receivedAndExpected[id-1].first == receivedAndExpected[id-1].second)
    //         {
    //             tPos++;
    //         }
    //         else
    //         {
    //             fNeg++;
    //         }

    //     }
    //     else
    //     {
    //         if (receivedAndExpected[id-1].first == receivedAndExpected[id-1].second)
    //         {
    //             fPos++;
    //         }
    //         else
    //         {
    //             tNeg++;
    //         }
    //     }
    //     std::cout << id << std::endl;
    //     std::cout << tPos << tNeg << fPos << fNeg << std::endl;
    //     accuracys.push_back(accuracy(tPos,tNeg,fPos,fNeg));
    //     // double recalli = recall(tPos,fNeg);
    //     // double presicioni = presicion(tPos,fNeg);
    //     // recalls.push_back(recalli);
    //     // presicions.push_back(presicioni);
    //     // mediaArmonicas.push_back(mediaArmonica(presicioni,recalli));
    // }


    return 0;
}