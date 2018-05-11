#include "imagen.h"
#include "pca.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// std::vector<Imagen> cargarBD(std::string csv)
// {
//
//
//     std::vector<Imagen> baseDeDatos = {};
//     std::ifstream input(csv);
//     char delimiter(',');
//
//     std::string imagen;
//     std::string line;
//     int id;
//     int i = 0;
//
//     while (std::getline(input, line,delimiter)){
//
//     // for( std::string line; std::getline( input, line, delimiter);){
//         imagen = line;
//         if (i != 0)
//             imagen = line.substr(1, line.size());
//
//        std::getline( input, line, delimiter);
//
//         std::stringstream(line) >> id;
//         Imagen nuevaImagen(imagen,id);
//         baseDeDatos.push_back(nuevaImagen);
//
//         i++;
//     }
//     return baseDeDatos;
// }















baseDeDatos cargarBD(std::string csv)
{
    baseDeDatos base = {};
    std::ifstream input(csv);

    std::string imagen;
    std::string line;
    int id;


    while (std::getline(input, line))
    {
      std::cout <<  "line " << line << "\n";

      std::size_t found = line.find_first_of(", ");      //primer delimitador
      // if (found!=std::string::npos)
      // {
        imagen = line.substr(0, found);
        line = line.substr(found, line.size()-1);

        std::size_t inicio = line.find_first_not_of(", "); //inicio de datos significativos
        // if (inicio!=std::string::npos)
        // {
          line = line.substr(inicio, line.size()-1);
          id = std::stoi (line);
std::cout <<  "imagen: " << imagen << "\n";
std::cout <<  "id: " << id << "\n";
          Imagen nuevaImagen(imagen,id);

          base.push_back(nuevaImagen);
    }
    return base;
}


// std::size_t inicio = line.find_first_not_of(", "); //inicio de datos significativos
// if (inicio!=std::string::npos)
// {
//   line = line.substr(inicio, line.size());
  // std::size_t found = line.find_first_of(", ");      //primer delimitador
  // if (found!=std::string::npos)
  //   cid = line.substr(0, found-1);
  //   id = std::stoi (line,&sz);
  // else
  //   cid = line.substr(0, line.size());








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
    std::cout << "entrando a Imagen: " << archivo << " \n";
    bool ret = LoadPPMFile(&_data, &_width, &_height, &pt, archivo.c_str());
    std::cout << "ancho, alto, pt: " << _width << " " << _height << " " << pt << "\n";
    if (!ret || _width == 0|| _height == 0|| pt!=PPM_LOADER_PIXEL_TYPE_GRAY_8B )
    {
        throw std::runtime_error("test_load failed");
    }
    //std::cout << "data: " <<
    _id = id;
    std::cout << "saliendo de Imagen: \n";
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

Imagen::Imagen (const Imagen &viejo)
{
    int tam = viejo._width * viejo._height;
    _data = new uchar[tam];
    for (int i=0; i<tam; ++i)
    {
      _data[i] = viejo._data[i];
    }
    _width = viejo._width;
    _height = viejo._height;
    _maxVal = viejo._maxVal;
    _id = viejo._id;
}

Imagen& Imagen::operator=(const Imagen& viejo)
{

  int tam =_width * _height;

    uchar* localdata = new uchar(tam);
    for (int i=0; i<tam; ++i)
    {
      localdata[i] = viejo._data[i];
    }
    delete[] _data;
    _data = localdata;

    _width = viejo._width;
    _height = viejo._height;
    _maxVal = viejo._maxVal;
    _id = viejo._id;
    return *this;
}
