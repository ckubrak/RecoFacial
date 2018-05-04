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
    for (int i=0; i < _elementos.size(); i++)
    { 
        resta._elementos.push_back( _elementos[i] - otra._elementos[i]);
    }

    double res = 0;

    for (int j = 0; j < _elementos.size(); j++)
    {
        res += resta._elementos[j];
    }
    return sqrt(double(res));
}


Imagen::Imagen(char* archivo, int id)
{
	FILE* fid = fopen(archivo, "rb");
	if (!fid) {
		printf("PGM load error: file access denied %s\n", archivo);
		return;
	}
	// Read PPM/PGM header P5/P6
	int channels = 0;
	char line[256];
    char *ptr;
	fgets(line, 256, fid);

    //B&W only
	if ( line[0]!='P' || line[1]!='5' ) {
		printf("Wrong image type\n");
		return;

    if (line[2] == '\n') {
        fgets(line, 256, fid);

        // Parse comments
        fgets(line, 256, fid);
        while(line[0]=='#')
          fgets(line, 256, fid);

        ptr = line;
    } else
        ptr = line + 3;

        // Read dimensions
        _ancho = strtol(ptr, &ptr, 10);
        _alto = strtol(ptr, &ptr, 10);
        if(ptr == NULL || *ptr == '\n'){
            fgets(line, 256, fid);
            ptr = line;
        }

// 	// Read pixel depth
//     int levels = strtol(ptr, &ptr, 10);
//   int pixel_depth = 0;
// 	if (channels==3 && (levels == 255)) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_RGB_8B;
// 		pixel_depth = 1;
// 	}else if (channels==3 && levels == 65535) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_RGB_16B;
// 		pixel_depth = 2;
// 	} else if (channels==3 && levels == 4294967295) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_RGB_32B;
// 		pixel_depth = 4;
// 	} else if (channels==3 && levels == 18446744073709551615U) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_RGB_64B;
// 		pixel_depth = 8;		
// 	}else if (levels == 255) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_8B;
// 		pixel_depth = 1;
// 	}else if (levels == 65535) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_16B;
// 		pixel_depth = 2;
// 	} else if (levels == 4294967295) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_32B;
// 		pixel_depth = 4;
// 	} else if (levels == 18446744073709551615U) {
// 		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_64B;
// 		pixel_depth = 8;
// 	} else {
// 		printf("ERROR: Wrong number of levels\n");
// 		return false;
	}

	// Read raw data from file
	// int size = (*width) * (*height) * channels * pixel_depth;
	// *data = new uchar[size];
	// fread(*data, 1, size, fid);
	fclose(fid);
    _id = id;
}

Imagen::Imagen()
{
    _elementos = {};
    _ancho = 0;
    _alto = 0;
    _maxVal = 0;
    _id = -1;
}
