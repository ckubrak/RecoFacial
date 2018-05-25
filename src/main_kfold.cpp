#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"

double precision(int truePos, int falsePos)
{
    if(truePos+falsePos == 0)
        return -1;
    return double(truePos/(truePos + falsePos));
}
double recall(int truePos, int falseNeg)
{
    if(truePos+falseNeg == 0)
        return -1;
    return double(truePos/(truePos + falseNeg));
}

double accuracy(int truePos, int trueNeg, int falsePos, int falseNeg)
{
    std::cout << truePos << " " << trueNeg << " " << falsePos << " " <<  falseNeg<<std::endl;
    double top = double(truePos) + double(trueNeg);
    return top/(truePos + trueNeg + falsePos + falseNeg);
}
double mediaArmonica(double precision, double recall)
{
    if (recall == -1 || precision == -1 )
        return -1;
    return 2 * (precision*recall/(precision + recall));
}
int main_kfold(int pca, int k, int alfa, int kknn)
{
    int method;
    std::string trainSet = "../tests/testFullRed.in";

    // int pca = 0;
    // int k = 1; // TODO variar
    // int alfa = 20; // TODO variar

    baseDeDatos baseEntrenamiento = cargarBD(trainSet);
    std::cout << "Size: " << baseEntrenamiento.size() << std::endl;

    vector<vector<pair<int, int> > > vectorDeFolds = k_fold(baseEntrenamiento, k, pca, alfa, kknn);

            // CAMBIAR 41 por cantSujetos
            int cantSujetos = 41; 
    std::vector<double> accuracyI(cantSujetos-1,0.0);
    std::vector<double> recallI(cantSujetos-1,0.0);
    std::vector<double> precisionI(cantSujetos-1,0.0);
    std::vector<double> mediaArmonicaI(cantSujetos-1,0.0);

        std::vector<int> truePositivesId(cantSujetos-1,0);
        std::vector<int> trueNegativesId(cantSujetos-1,0);
        std::vector<int> falsePositivesId(cantSujetos-1,0);
        std::vector<int> falseNegativesId(cantSujetos-1,0);
    for (int fold = 0; fold < vectorDeFolds.size(); fold++ )
    {

        std::fill(truePositivesId.begin(), truePositivesId.end(), 0);
        std::fill(falsePositivesId.begin(), falsePositivesId.end(), 0);
        std::fill(trueNegativesId.begin(), trueNegativesId.end(), 0);
        std::fill(falseNegativesId.begin(), falseNegativesId.end(), 0);

        for (int i = 0; i < vectorDeFolds[fold].size(); i++)
        {

            for (int id = 1; id <= cantSujetos; id++)
            {

                if (id == vectorDeFolds[fold][i].first)
                {
                    if (vectorDeFolds[fold][i].first == vectorDeFolds[fold][i].second)
                    {
                        truePositivesId[id-1] += 1;
                    }
                    else
                    {
                        falseNegativesId[id-1] += 1;
                    }
                }
                else
                {

                    if (vectorDeFolds[fold][i].first == vectorDeFolds[fold][i].second)
                    {
                        falsePositivesId[id-1] += 1;
                    }
                    else
                    {
                        trueNegativesId[id-1] += 1;
                    }
                }
            }
        }
    }

    for (int j = 0; j < truePositivesId.size(); j++)
    {
        accuracyI[j] = accuracy(truePositivesId[j], trueNegativesId[j], falsePositivesId[j],falseNegativesId[j]);
        recallI[j] = recall(truePositivesId[j],falseNegativesId[j]);
        precisionI[j] = precision(truePositivesId[j],falsePositivesId[j]);
        mediaArmonicaI[j] = mediaArmonica(precisionI[j],recallI[j]);
    }
    double acc = 0;
    double recall = 0;
    double precision = 0;
    double mediaArmonica = 0;
    for (int l = 0; l < accuracyI.size(); l++)
    {
        if (accuracyI[l] == -1)
        {
            acc = -1;
            break;
        }
        acc += accuracyI[l];
    }
    
    for (int l = 0; l < recallI.size(); l++)
    {
        if (recallI[l] == -1)
        {
            recall = -1;
            break;
        }
        recall += recallI[l];
    }
    for (int l = 0; l < precisionI.size(); l++)
    {
        if (precisionI[l] == -1)
        {
            precision = -1;
            break;
        }
        precision += precisionI[l];
    }
    for (int l = 0; l < mediaArmonicaI.size(); l++)
    {
        if (mediaArmonicaI[l] == -1)
        {
            mediaArmonica = -1;
            break;
        }
        mediaArmonica += mediaArmonicaI[l];
    }
    acc = acc/accuracyI.size();
    recall = recall/accuracyI.size();
    precision = precision/accuracyI.size();
    mediaArmonica = mediaArmonica/accuracyI.size();
    std::cout << "Acc "<<acc << std::endl;
    std::cout << "Recall "<<recall << std::endl;
    std::cout << "Pres "<<precision << std::endl;
    std::cout << "mediaArm "<<mediaArmonica << std::endl;

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