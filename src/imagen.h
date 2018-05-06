#ifndef _VECINOS_
#define _VECINOS_

#include <vector>
#include <math.h>       /* sqrt */
#include <string>
#include <iostream>
#include <fstream>

typedef unsigned char uchar;


class Imagen 
{

    public:
        Imagen(char* archivo, int id);
        Imagen();

        double restarYnorma (const Imagen& otra);
    private:
         std::vector<uchar> _elementos;
         int _ancho;
         int _alto;
         int _maxVal;
         int _id;
};

std::vector<Imagen> cargarBD(char* archivo);


#endif