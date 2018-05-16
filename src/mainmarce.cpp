#include "imagen.h"
#include "pca.h"


int main()
{

    doubleMatrix transfCaracteristica = {};
    //CAMBIAR BASEDEDATOS
    std::string archivo = "../tests/testRed.in";
    std::cout << archivo << std::endl;
    baseDeDatos base = cargarBD(archivo);
    std::cout << base.size();
//    for (int i = 0; i<base.size();i++)
//    {
//        std::cout << base[i].getData() << " " << base[i].getId() << std::endl;
 //   }


    // 200 es el alfa que es un parametro leido en la linea de comandos
    PCA (base, transfCaracteristica, 200);

    return 0;
}
