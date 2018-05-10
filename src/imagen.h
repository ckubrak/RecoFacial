#ifndef _IMAGEN_H_
#define _IMAGEN_H_

#include <vector>
#include <math.h>       /* sqrt */
#include <string>
#include <iostream>
#include <fstream>


#include "../ppmloader/ppmloader.h"

typedef unsigned char uchar;


class Imagen 
{

    public:
        Imagen(std::string archivo, int id);
        Imagen();
        ~Imagen();

        uchar* getData();
        int size();
        int getId();
        int getHeight();
        int getWidth();
        double restarYnorma (const Imagen& otra);
    private:
        uchar* _data;
        int _width;
        int _height;
        int _maxVal;
        int _id;
};

std::vector<Imagen> cargarBD(std::string archivo);


#endif