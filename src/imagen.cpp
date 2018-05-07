#include "imagen.h"

std::vector<Imagen> cargarBD(char* csv)
{

    std::ifstream infile(csv);
    Imagen temp;

    char* imagen;
    int id;
    std::vector<Imagen> baseDeDatos = {};
    while (infile >> imagen >> id)
    {
        if (baseDeDatos.size() <= id)
        {
            baseDeDatos.resize(id - baseDeDatos.size());
        }
        baseDeDatos[id] = Imagen(imagen,id);
    }
}

double Imagen::restarYnorma (const Imagen& otra)
{
    Imagen resta;
    for (int i=0; i < _width * _height; i++)
    { 
        resta._data[i] =  _data[i] - otra._data[i];
    }

    double res = 0;

    for (int j = 0; j < _width * _height; j++)
    {
        res += resta._data[j];
    }
    return sqrt(double(res));
}


Imagen::Imagen(std::string archivo, int id)
{
    uchar* data = NULL;
    int width = 0, height = 0;
    PPM_LOADER_PIXEL_TYPE pt = PPM_LOADER_PIXEL_TYPE_INVALID;

    bool ret = LoadPPMFile(&_data, &_width, &_height, &pt, archivo.c_str());
    if (!ret || _width == 0|| _height == 0|| pt!=PPM_LOADER_PIXEL_TYPE_GRAY_8B )
    {
        throw std::runtime_error("test_load failed");
    }

    _id = id;
}

Imagen::Imagen()
{
    _data = {};
    _width = 0;
    _height = 0;
    _maxVal = 0;
    _id = -1;
}

Imagen::~Imagen()
{
    delete _data;
}

uchar* Imagen::getData()
{
    return _data;
}

int Imagen::getHeight()
{
    return _height;
}


int Imagen::getWidth()
{
    return _width;
}

int Imagen::getId()
{
    return _id;
}