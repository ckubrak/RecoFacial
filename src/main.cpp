#include "imagen.h"
#include "pca.h"
#include "knn.h"
#include "kfold.h"
#include "misc.h"

int main(int argc, char* argv[])
{
    // int method;
    // std::string trainSet, testSet, results;
    // for (int i = 1; i < argc; ++i)
    // {

    //     std::cout <<argv[i] <<std::endl;
    //     std::string toParse = argv[i];
    //     if (toParse == "-m")
    //     {
    //         std::cout << "m";
    //         method = atoi(argv[i+1]);
    //     }
    //     else if (toParse == "-i") 
    //     {
    //         trainSet = argv[i+1];
    //     }
    //     else if (toParse == "-q")
    //     {
    //         testSet = argv[i+1];
    //     }
    //      else if (toParse == "-o")
    //     {
    //         results = argv[i+1];
    //     }

    // }

    // int result;
    // int k = 5; // TODO variar
    // int alfa = 5; // TODO variar
    // baseDeDatos baseEntrenamiento = cargarBD(testSet);
    // std::ifstream input(testSet);
    // std::string imagen;
    // std::string line;
    // std::vector<std::vector<int> > vectordeKCercanos;
    // while (std::getline(input, line))
    // {



    //     std::size_t found = line.find_first_of(", ");      //primer delimitador
    //     imagen = line.substr(0, found);
 
    //     line = line.substr(found, line.size()-1);

    //     std::size_t inicio = line.find_first_not_of(", "); //inicio de datos significativos
    //       line = line.substr(inicio, line.size()-1);
    //      int id = std::stoi (line);
    //     Imagen nuevaImagen(imagen,-1);
 
    //     if (method == 0)
    //     {
    //         ofstream fileOUT("filename.txt", ios::app);
    //         result = moda(k, baseEntrenamiento, nuevaImagen);
    //     }
    //    else 
    //     {
    //         result = moda(k, baseEntrenamiento, nuevaImagen);
    //     }
    // }
    // return 0;
    return main_kfold();
} 