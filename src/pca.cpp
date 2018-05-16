#include "imagen.h"
#include "pca.h"


void printVector(doubleVector v)
{
  int filas = v.size();
  //imprimir vector
    for (int i=0;i<filas;i++){

        std::cout << v[i] << " ";

      std::cout << "\n";
    }

}

void printMatrix(doubleMatrix M)
{
  int filas, columnas;
  filas = M.size();
  columnas = M[0].size();
  for (int i=0;i<filas;i++){
    for (int j=0;j<columnas;j++){
      std::cout << M[i][j] << " ";
    }
    std::cout << "\n";
  }
}

double norma2Vectorial(doubleVector v)
{
  double acumulador=0.0;

  int n = v.size();
  //for (doubleVector::iterator it = v.begin() ; it != v.end(); ++it)
  for (int i=0; i<n; ++i)
  {
      acumulador+=pow(v[i],2);
  }
  return (sqrt(acumulador));
}

double normaInfinitoVectorial(doubleVector v, int &indice)
{
  double acumulador=0.0;
  indice = 0;
  int n = v.size();

  for (int i=0; i<n; ++i)
  {
      if (fabs(v[i])>acumulador){
        acumulador=fabs(v[i]);
        indice=i;
      }
  }
  return acumulador;
}

//por ahora para matrices cuadradas
double normaInfinitoMatricial(doubleMatrix x, int &indice)
{
  double temp=0.0;
  double norma=0.0;
  indice = 0;
  int n = x.size();
  int m;
  if (n>0) m=x[0].size();

  for (int i=0; i<n; ++i)
  {
    for (int j=0; j<m; ++j){
      temp += fabs(x[i][j]);
    }
      if (temp>norma){
        norma=temp;
        indice=i;
      }
      temp = 0.0;
  }
  return norma;
}




// matriz y vectores no vacios
doubleVector matrizXVector(doubleMatrix A, doubleVector v)
{
  int n=A.size();
  doubleVector y(n);
  double acumulador = 0.0;
  //int n=A.size();
  int m;

  if (n>0)
  {
    m = A[0].size();
  }
  for (int i = 0 ; i != n; ++i)
  {
      for (int j=0 ; j != m; ++j)
      {
        acumulador += A[i][j]*v[j];
      }
      y[i]=acumulador;
      //y.push_back(acumulador);
      acumulador=0.0;
  }
  return y;
}

////// matriz  por matriz: asumimos que las dimensiones son validas  //////////
doubleMatrix matrizXMatriz(doubleMatrix A, doubleMatrix B)
{
  int n=A.size(); //filas de A
  int m=B.size(); //filas de B, columnas de A
  int r; //columnas de B

  if (A.size()>0)
    m = B.size();

  if (m>0)
    r=B[0].size();

  doubleMatrix R(n, doubleVector(r));
  double acumulador = 0.0;
  //calcular R[i][j]
  for (int i = 0 ; i != n; ++i)
  {
    for (int j=0 ; j != r; ++j)
    {
      acumulador=0.0;
      for (int k=0; k<m; ++k)
      {
            acumulador += A[i][k]*B[k][j];
      }
      R[i][j]=acumulador;
    }
  }
  return R;
}

doubleMatrix vvt(doubleVector v)
{
  int n=v.size(); //fstd::vlas de A
  doubleMatrix R (n, doubleVector(n));
  double acumulador = 0.0;
//  int n=v.size(); //filas de A

  //calcular R[i][j]
  for (int i = 0 ; i != n; ++i)
  {
    for (int j=0 ; j != n; ++j)
    {
      acumulador = 0.0;
      acumulador += v[i]*v[j];
//      R[i].push_back(acumulador);
      R[i][j]=acumulador;
    }
    // R[i].push_back(acumulador);
    // acumulador=0.0;
  }
  return R;
}

doubleMatrix matrizXEscalar(doubleMatrix A, double esc)
{
  int m;

  int n = A.size();
  if (A.size() > 0) m=A[0].size();

  for (int i = 0; i != n; ++i)
  {
      for (int j=0; j != m; ++j)
      {
        A[i][j] *= esc;
      }
  }  return A;
}

doubleVector vectorXEscalar(doubleVector v, double esc)
{

      for (doubleVector::iterator j = v.begin() ; j != v.end(); ++j)
      {
        *j *= esc;
      }

  return v;
}


doubleVector sumaVectorial(doubleVector a, doubleVector b)
{
  int s=a.size();
  for (int i=0; i<s; ++i)
  {
    a[i] += b[i];
  }
  return a;
}

doubleVector restaVectorial(doubleVector a, doubleVector b)
{
  return sumaVectorial(a,vectorXEscalar(b, -1.0));
}


doubleMatrix sumaMatricial(doubleMatrix a, doubleMatrix b)
{
  int s=a.size();
  int t=a[0].size();
  for (int i=0; i<s; ++i)
  {
    for (int j=0; j<t; ++j)
      a[i][j] += b[i][j];
  }
  return a;
}

doubleMatrix restaMatricial(doubleMatrix a, doubleMatrix b)
{
  return sumaMatricial(a,matrizXEscalar(b, -1.0));
}


// ver si hay que normalizar Ax
// iterar hasta   que en dos iteraciones sucesivas la diferencia entre las normas sea menor que la tolerancia
// si se normaliza el vector al mismo tiempo se calcula el autovalor dominante
//
// int MetodoPotencias(doubleMatrix A, doubleVector x,int nroIter,float tol, double &autoval, doubleVector &autovec)
// {
//
//   double norma, lambda;
// //  double nant=0.0;
//   int indice=0; //indice del elemento que define la norma infinito
//   int sz=x.size();
//   double r=1.0;
//
//   std::cout << "entrando a potencias: \n";
//
//   for (int i= 0; i<x.size(); ++i) {
//     std::cout << x[i]  << " ";
//   }
//   std::cout << std::endl;
//
//   //normalizo el vector x
//   //nx = norma2Vectorial(x);
//   norma = normaInfinitoVectorial(x, indice);
//   lambda = x[indice];
//   x = vectorXEscalar(x, 1.0/lambda);
//
//   for (int i= 0; i<x.size(); ++i) {
//     std::cout << x[i]  << " ";
//   }
//   std::cout << std::endl;
//   doubleVector y(sz); // guarda el valor de la ultima iteracion
//   int k=0;
//   while (k<nroIter && r > tol)
//   {
//
//     y = matrizXVector(A, x);
//     std::cout << "despues de llamar matrizXvector: \n";
//     for (int i= 0; i<y.size(); ++i) {
//       std::cout << y[i]  << " ";
//     }
//     std::cout << std::endl;
//
//     norma = normaInfinitoVectorial(y, indice);
//     std::cout << "norma: " << norma << "\n";
//     if (norma < 0.00000001)  // considero que la norma es cero, no puedo dividir por ella
//     {
//         lambda = 0;
//         break;  //no hubo convergencia
//     }
//     lambda=y[indice];
//     y = vectorXEscalar(y, 1/lambda);
// std::cout << "y[indice] despues de normalizar: " << y[indice] << "\n";
//     r = normaInfinitoVectorial(restaVectorial(x,y), indice);
//
//     x = y;
//
//     k++;
//   }
//
//   // analizar si hubo convergencia. Si no la hubo habria que intentar con otro x inicial
//   if (r > tol)
//     return 0; //no hubo convergencia
//   else
//   {
//     autovec = x;
//     autoval = lambda;
//     return 1; // hubo convergencia
//   }
// }
//
//
//
// int MetodoPotencias2(doubleMatrix A, doubleVector x,int nroIter,float tol, double &autoval, doubleVector &autovec)
// {
//
//   double normax, normay, lambda, auxlambda;
// //  double nant=0.0;
// int indice;
//   int sz=x.size();
//   double r=1.0;
//
//   std::cout << "entrando a potencias: \n";
//
//   for (int i= 0; i<x.size(); ++i) {
//     std::cout << x[i]  << " ";
//   }
//   std::cout << std::endl;
//
//   //normalizo el vector x
//   //nx = norma2Vectorial(x);
//   normax = normaInfinitoVectorial(x, indice);
//   lambda = normax;
//   autovec = x;
//   auxlambda = normax;
//
//   x = vectorXEscalar(x, 1.0/normax);//normalizamos x
//
//   for (int i= 0; i<x.size(); ++i) {
//     std::cout << x[i]  << " ";
//   }
//   std::cout << std::endl;
//   doubleVector y(sz); // guarda el valor de la ultima iteracion
//   int k=0;
//
//   while (k<nroIter && r > tol)
//   {
//
//     y = matrizXVector(A, x);
//     std::cout << "despues de llamar matrizXvector: \n";
//     for (int i= 0; i<y.size(); ++i) {
//       std::cout << y[i]  << " ";
//     }
//     std::cout << std::endl;
//
//     normay = normaInfinitoVectorial(y, indice);
//     std::cout << "normay: " << normay << "\n";
//     if (normax < 0.0000001)  // considero que la norma es cero, no puedo dividir por ella
//     { //PENDIENTE VER QUE RETORNAR CUANDO LA NORMA TIENDE A CERO
//         lambda = 0;
//         break;  //no hubo convergencia
//     }
//     auxlambda=lambda;
//     //lambda=normay/normax;
//     //lambda=normay;
//     y = vectorXEscalar(y, 1/normay);
//
//     r = fabs(normax-normay); // variacion del autovalor en dos iteraciones sucesivas
//
//     x = y;
//     normax = normay;
//
//     k++;
//   }
//
//   // analizar si hubo convergencia. Si no la hubo habria que intentar con otro x inicial
//   if (r > tol)
//     return 0; //no hubo convergencia
//   else
//   {
//     autovec = x;
//     autoval = normax;
//     return 1; // hubo convergencia
//   }
// }
//

int MetodoPotencias(doubleMatrix A, doubleVector x,int nroIter,float tol, double &autoval, doubleVector &autovec)
{

  double normax, normay, lambda;//, auxlambda;
//  double nant=0.0;
int indice;
  int sz=x.size();
  double r=1.0;

  std::cout << "entrando a potencias: \n";

  for (int i= 0; i<x.size(); ++i) {
    std::cout << x[i]  << " ";
  }
  std::cout << std::endl;

  //normalizo el vector x
  //nx = norma2Vectorial(x);
  normax = norma2Vectorial(x);
  lambda = normax;
  autovec = x;
  //auxlambda = normax;

  x = vectorXEscalar(x, 1.0/normax);//normalizamos x

  // for (int i= 0; i<x.size(); ++i) {
  //   std::cout << x[i]  << " ";
  // }nroIter
  //std::cout << std::endl;
  doubleVector y(sz); // guarda el valor de la ultima iteracion
  int k=0;

  while (k<nroIter && r > tol || (k>=nroIter && k<nroIter*10 && r>0.001))
  {

    y = matrizXVector(A, x);
  //  std::cout << "despues de llamar matrizXvector: \n";
    // for (int i= 0; i<y.size(); ++i) {
    //   std::cout << y[i]  << " ";
    // }
    // std::cout << std::endl;

    normay = norma2Vectorial(y);
    //std::cout << "normay: " << normay << "\n";
    if (normay < 0.0000001)  // considero que la norma es cero, no puedo dividir por ella
    { //PENDIENTE VER QUE RETORNAR CUANDO LA NORMA TIENDE A CERO
        lambda = 0;
        break;  //no hubo convergencia
    }
    //auxlambda=lambda;
    //lambda=normay/normax;
    //lambda=normay;
    y = vectorXEscalar(y, 1/normay);

    r = fabs(normax-normay); // variacion del autovalor en dos iteraciones sucesivas

    x = y;
    normax = normay;

    k++;
  }

  // analizar si hubo convergencia. Si no la hubo habria que intentar con otro x inicial
  if (r > tol)
    return 0; //no hubo convergencia
  else
  {
    autovec = x;
    autoval = normax;
    return 1; // hubo convergencia
  }
}





//Entrada: matriz, cantidad de autovalores significativos.
//Salida: vector con autovalores, matriz de autovectores (uno por fila)
// los autovectores se almacenan por fila (ojo!!! No por columna!!!)
//PENDIENTE: definir la dimension de los parametros de salida en funcion del alfa?????????
int Deflacion(doubleMatrix A, int alfa, doubleVector &autovalores, doubleMatrix &autovectores)
{
  //PENDIENTE
  long dimension=A[0].size();
  doubleVector x(dimension);
  double tol=0.00001;
  int nroIter=10000;
  double lambda;

  doubleVector autovec(dimension);
  doubleMatrix auxA(dimension, doubleVector(dimension));

  //autovec.reserve(dimension);

  //averiguo autoval ppal y vector asociado
  //ir almacenando los autovalores y autovectores que se van hallando
  //repetir para A-lambda*v1*v1t

  // armar vector x inicial en funcion de la dimension de la matriz A
  //analizar opciones de como armarlo PENDIENTE
  /* initialize random seed: */
  srand (time(NULL));
  /* generate secret number between 1 and 10: */
  for (int i=0; i<dimension; ++i)
    x[i]=rand() % dimension + 1;

  for (int d=0; d<dimension && d<alfa; ++d)
  {

    if (MetodoPotencias(A, x, nroIter, tol, lambda, autovec) == 1) //hubo convergencia
    {
      //Almacenar valores obtenidos para el autovalor y autovector ppal
      autovalores[d]=lambda;
      autovectores[d]=autovec;
      if (d<dimension-1){
        auxA = vvt(autovec);
        auxA = matrizXEscalar(auxA, lambda);
        A=restaMatricial(A, auxA);
        //restaMatricial
      }
        //A = restaMatricial(A, matrizXEscalar(vvt(autovec), lambda));
    }
    else
    {
      //fallo el metodo de la potencia
       std::cout << "no hubo convergencia metodo de las potencias\n";
       std::cout << "d: " << d << " " << autovalores[d];
    }
  }
  //std::cout << "saliendo deflacion\n";
}

// se calcula X*Xt. Por ahora no lo uso: se obtiene una matriz de n x n (n=cantidad de imagenes)
void CalcularCovarianza(doubleMatrix X, int filas, int columnas, doubleMatrix &mcov){
    //Xt*X
    double acumulador=0;

    //reservo espacio para la matriz de dimension filas por filas
    // mcov.reserve(filas);
    // for (int i=0; i<filas; i++)
    //   mcov[i].reserve(filas);

    for (int i=0; i<filas; i++){
      for (int j=0; j<filas; j++){
        acumulador=0.0;
        for (int k=0; k<columnas; k++)
          acumulador+=X[i][k]*X[j][k];
        //mcov[i].push_back(acumulador);
        mcov[i][j] = acumulador;
      }
    }
//std::cout << "antes de salir de CalcularCovarianza \n";
}



//Arma en el parametro de Salida X una matriz con las imagenes normalizadas
void ArmarMatrizX(baseDeDatos muestra, doubleVector media, int filas, int columnas, doubleMatrix &X )
{
  float den;

  den=sqrt(filas-1);
//   std::cout << "dentro armar X. filas, columnas, X.size, X.capacity: " << filas << " " << columnas << " " << X.size() << " " << X.capacity() << std::endl;
// std::cout << "Filas " << filas << " colmunas " << columnas;
  for (int i=0;i<filas;i++){
    for (int j=0;j<columnas;j++){
        // std::cout << "I " << i << " J " << j<<std::endl;
        // std::cout << filas << " cols " << columnas<<std::endl;
        X[i][j]= (muestra[i].getData()[j] - media[j])/den ;
        //std::cout << "fila i de X, size X, X[i].size(): " << i << " " << X.size() << " " << X[i].size() << std::endl;
    }
  }
//  std::cout << "saliendo de armar X \n";
}


// resultado: alfa * columnas
doubleMatrix matrizTraspuesta (doubleMatrix A)
{
  int filas, columnas;

  filas = A.size();
  if (filas > 0) columnas = A[0].size();

  doubleMatrix B (columnas, doubleVector(filas));

  for (int i=0; i<filas; ++i){
    for (int j=0; j<columnas; ++j){
      B[j][i]=A[i][j];
    }
  }
  return B;
}




// Recibe como parametro la base de datos con todas las imagenes
// parametro de salida una matriz con la transformacion caracteristica de cada imagen
// columnas = cantidad de bytes por imagenes. Se puede calcular a partir de una de las imagenes cualquiera
// multiplicando ancho por alto.
void PCA (baseDeDatos muestra, doubleMatrix &matrizCaracteristicaMuestra, int alfa){

  int filas, columnas;

  //std::cout << "dentro de PCA\n";
  filas = muestra.size();
  std::cout << "filas: " << filas << "\n";

  // las columas es ancho * alto de la imagenes
  // Asumiendo que son todas de la misma dimension uso lo de la primera
  columnas=muestra[0].getWidth()*muestra[0].getHeight();
  std::cout << "columnas: " << columnas << "\n";

  doubleVector media;
  media.reserve(columnas);

  for (int j=0; j<columnas;j++)
    media.push_back(0.0);
  std::cout << "fin inicializacion media\n";

  //calcular la media de cada columnas
  for (int j=0;j<columnas;j++){
    for (int i=0;i<filas;i++){
  //    std::cout << (double)muestra[i].getData()[j] << " ";
      media[j]+= (double)muestra[i].getData()[j];
    }
    //std::cout << "\n";
  }

  //std::cout << "media:\n";
  for (int j=0;j<columnas;j++){
    media[j]=media[j]/filas;
  }

  // //imprimir media
  // for (int j=0;j<columnas;j++){
  //     std::cout << media[j] << " ";
  // }
  // std::cout << "\n";


  doubleMatrix X(filas, doubleVector(columnas));
//  std::cout << "antes de armar matriz\n";
  ArmarMatrizX(muestra, media, filas, columnas, X);
// //imprimir X
//   for (int i=0;i<filas;i++){
//     std::cout << "va a imprimir fila X[i]: " << i << std::endl;
//     for (int j=0;j<columnas;j++){
//       std::cout << X[i][j] << " ";
//     }
//     std::cout <<  "\n";
//   }

//std::cout << "despues de imprimir X \n";
//Calcular Xt*X = Matriz de covarianza // Se va a hacer X * Xt y despues se van a calcular los valores singulares de la otra
//para trabajar con matrices mas chicas
  doubleMatrix mcov(filas, doubleVector(filas));

  CalcularCovarianza (X, filas, columnas, mcov);

  // for (int i=0;i<filas;i++){
  //   std::cout << "covarianza calculada fila mcov[i]: " << i << std::endl;
  //   for (int j=0;j<filas;j++){
  //     std::cout << mcov[i][j] << " ";
  //   }
  //   std::cout <<  "\n";
  // }

  // LLamar al metodo de deflacion para calcular los autovalores y autovectores
  // usar el parametro alfa para ver cuantos hay que averiguar

  doubleVector autovalores(alfa);
  doubleMatrix autovectores(alfa, doubleVector(mcov.size()) );
  std::cout << "antes de llamar Deflacion" << std::endl;
  int r= Deflacion(mcov, alfa, autovalores, autovectores);
  std::cout << "despues de deflacion: " << std::endl;

  // for (int i=0;i<mcov.size();i++){
  //   std::cout << "va a imprimir fila autovectores[i]: " << i << std::endl;
  //   for (int j=0;j<filas;j++){
  //     std::cout << mcov[i][j] << " ";
  //   }
  //   std::cout <<  "\n";
  // }

  // Convertir los autovalores y autovectores calculados en los correspondientes de la matriz Xt * X
  //Ui=Xt*autovectores(i)/sqrt(autovalores(i))
  //Primero calcular los autovalores
  for (int i=0;i<alfa;i++){
    std::cout << "va a imprimir autovalores[i]: " << i << ": ";
    autovalores[i]=sqrt(autovalores[i]);

    std::cout << autovalores[i] << " ";
  }
  std::cout <<  "\n";


  //Usando los autovalores calculados recalcular los autovectores
  //for (int i=0;i<alfa;i++){
    //Hay que multiplicar Xt * autovectores[i] / autovalores[i]
    // matrizXVector (Tras(X),Tras(autovectores))
    //dimensiones: autovectores(alfa * filas), X(filas * columnas)
    // filas=cantidad de imagenes, columnas= cantidad de variables originales
    // resultado: alfa * columnas
    for (int i=0; i<alfa; ++i)
      autovectores[i] = vectorXEscalar (autovectores[i],(1/autovalores[i])); // dividir el autovector i por el autovalor correspondiente

    matrizCaracteristicaMuestra = matrizTraspuesta (matrizXMatriz (autovectores, X));

  //}

  for (int i=0;i<alfa;i++){
    std::cout << "va a imprimir fila autovectores[i]: " << i << std::endl;
    for (int j=0;j<columnas;j++){
      std::cout << matrizCaracteristicaMuestra[i][j] << " ";
    }
    std::cout <<  "\n";
  }

}
