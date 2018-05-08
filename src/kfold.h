#ifndef _KFOLD_H_
#define _KFOLD_H_

#include <vector>
#include <math.h>       /* sqrt */
#include <string>
#include <iostream>
#include <fstream>
#include "pca.h"

void k_fold( baseDeDatos bd, int k, float tfold, int cmuestras, int cclases);

#endif
