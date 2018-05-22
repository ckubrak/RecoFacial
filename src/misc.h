#ifndef _MISC_H_
#define _MISC_H_

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
double mediaArmoncia(double presicion, double recall)
{
    return 2 * (presicion*recall/presicion + recall);
}
int main_kfold();
#endif