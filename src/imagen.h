#ifndef _VECINOS_
#define _VECINOS_

#include <vector>
#include <math.h>       /* sqrt */
#include <string>
#include <iostream>
#include <fstream>

typedef unsigned char uchar;

typedef 
enum _PPM_LOADER_PIXEL_TYPE {
	PPM_LOADER_PIXEL_TYPE_INVALID = -1,
	PPM_LOADER_PIXEL_TYPE_RGB_8B = 0,
	PPM_LOADER_PIXEL_TYPE_GRAY_8B = 1,
	PPM_LOADER_PIXEL_TYPE_GRAY_16B = 2,
	PPM_LOADER_PIXEL_TYPE_GRAY_32B = 3,
	PPM_LOADER_PIXEL_TYPE_GRAY_64B = 4
} PPM_LOADER_PIXEL_TYPE;

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
         PPM_LOADER_PIXEL_TYPE _pixelType;
};

std::vector<Imagen> cargarBD(char* archivo);


#endif