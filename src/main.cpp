#include "imagen.h"


int main()
{
    //CAMBIAR BASEDEDATOS
    std::string archivo = "../src/testFullBig.in";
    std::cout << archivo << std::endl;
    std::vector<Imagen> baseDeDatos = cargarBD(archivo);

    for (int i = 0; i<baseDeDatos.size();i++)
    {
        std::cout << baseDeDatos[i].getId();
    }
    return 0;
}
