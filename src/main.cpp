#include "imagen.h"
#include "pca.h"


int main()
{

    doubleMatrix transfCaracteristica = {};
    //CAMBIAR BASEDEDATOS
    std::string archivo = "../tests/testRed.in";
    std::cout << archivo << std::endl;
    baseDeDatos base = cargarBD(archivo);

    for (int i = 0; i<base.size();i++)
    {
        std::cout << base[i].getData() << " " << base[i].getId() << std::endl;
    }
    // asignar el espacio para la matriz de transformacion caracteristica dobles que se va a usar para llamar a kNN
    // PENDIENTE
    PCA (base, transfCaracteristica, 1);
    return 0;
}
