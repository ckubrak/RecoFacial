#include "imagen.h"
#include "pca.h"


int main()
{


    //CAMBIAR BASEDEDATOS
    //std::string archivo = "../tests/testFullBig.in";
    std::string archivo = "../tests/testRed.in";
    std::cout << archivo << std::endl;
    baseDeDatos base = cargarBD(archivo);

    int filas, columnas;
    filas = base.size();
    // las columas es ancho * alto de la imagenes
    // Asumiendo que son todas de la misma dimension uso lo de la primera
    columnas=base[0].getWidth()*base[0].getHeight();
    std::cout << "columnas: " << columnas << "\n";

    //    for (int i = 0; i<base.size();i++)
//    {
//        std::cout << base[i].getData() << " " << base[i].getId() << std::endl;
 //   }


    // 200 es el alfa que es un parametro leido en la linea de comandos
    // reservar espacio para los parametros de salida
    //doubleMatrix transfCaracteristicaMuestra(base.size(), doubleVector(alfa));
int alfa=200;
    doubleMatrix matrizCaracteristicaMuestra(filas, doubleVector(alfa));
    doubleMatrix cambioDeBase (alfa, doubleVector(columnas));
    doubleVector media (columnas);
    PCA (base, cambioDeBase, media, matrizCaracteristicaMuestra, 200);

    doubleVector img(columnas);
    img = ucharToDoubleVector (base[2].getData(), columnas);


    img = normalizarImagen (img, media, cambioDeBase, matrizCaracteristicaMuestra);

    for (int j=0; j<alfa; j++)
      std::cout << img[j] << ",";
    std::cout << "\n";

for (int i=0; i<filas; ++i){
    for (int j=0; j<alfa; j++)
      std::cout << matrizCaracteristicaMuestra[i][j] << ",";
}
    std::cout << "\n";



//void PCA (baseDeDatos muestra, doubleMatrix &tc, doubleVector &media, &matrizCaracteristicaMuestra, int alfa){

      std::cout << "main, va a imprimir autovectores reales: " << std::endl;
    for (int i=0; i<matrizCaracteristicaMuestra.size(); i++){
//      std::cout << "main, va a imprimir fila autovectores[i]: " << i << std::endl;
      for (int j=0; j<matrizCaracteristicaMuestra[i].size(); j++){
        std::cout << matrizCaracteristicaMuestra[i][j] << ",";
      }
      std::cout <<  "\n";
    }

    return 0;
}
