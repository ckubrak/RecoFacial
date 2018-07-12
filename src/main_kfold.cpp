#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"

double precision(int truePos, int falsePos)
{
    if(truePos+falsePos == 0)
        return -1;
    return double(truePos)/(double(truePos + falsePos));
}
double recall(int truePos, int falseNeg)
{
    if(truePos+falseNeg == 0)
        return -1;
    return double(truePos)/(double(truePos + falseNeg));
}

double accuracy(int truePos, int trueNeg, int falsePos, int falseNeg)
{
    double top = double(truePos) + double(trueNeg);
    return top/double((truePos + trueNeg + falsePos + falseNeg));
}
double mediaArmonica(double precision, double recall)
{
    if (recall == -1 || precision == -1 )
        return -1;
    double top = 2*(precision*recall);
    return top/double((precision + recall));
}
int main_kfold(int pca, int k, int alfa, int kknn)
{
    int method;
    std::string trainSet = "../tests/testFullRed.in";


    baseDeDatos baseEntrenamiento = cargarBD(trainSet);

    vector<vector<pair<int, int> > > vectorDeFolds = k_fold(baseEntrenamiento, k, pca, alfa, kknn);

    // CAMBIAR 41 por cantSujetos
    int cantSujetos = 41; 
    std::vector<double> accuracyI(cantSujetos,0.0);
    std::vector<double> recallI(cantSujetos,0.0);
    std::vector<double> precisionI(cantSujetos,0.0);
    std::vector<double> mediaArmonicaI(cantSujetos,0.0);

        std::vector<int> truePositivesId(cantSujetos,0);
        std::vector<int> trueNegativesId(cantSujetos,0);
        std::vector<int> falsePositivesId(cantSujetos,0);
        std::vector<int> falseNegativesId(cantSujetos,0);

    for (int fold = 0; fold < vectorDeFolds.size(); fold++ )
    {


        for (int i = 0; i < vectorDeFolds[fold].size(); i++)
        {

            for (int id = 1; id <= cantSujetos; id++)
            {
                if (id == vectorDeFolds[fold][i].first && id == vectorDeFolds[fold][i].second)
                  truePositivesId[id-1] += 1;
                else if (id == vectorDeFolds[fold][i].first && id != vectorDeFolds[fold][i].second)
                  falseNegativesId[id-1] += 1;
                else if (id != vectorDeFolds[fold][i].first && id == vectorDeFolds[fold][i].second)
                  falsePositivesId[id-1] += 1;
                else if (id != vectorDeFolds[fold][i].first && id != vectorDeFolds[fold][i].second)
                  trueNegativesId[id-1] += 1;

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
    std::cout <<acc<< " ";
    std::cout <<recall << " "; 
    std::cout <<precision << " ";
    std::cout <<mediaArmonica<< std::endl;


    return 0;
}