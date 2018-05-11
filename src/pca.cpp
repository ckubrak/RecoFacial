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


// matriz y vectores no vacios
doubleVector matrizXVector(doubleMatrix A, doubleVector v)
{
  doubleVector y;
  double acumulador = 0.0;
  int n=A.size();
  int m;

  if (A.size()>0)
  {
    m = A[0].size();
  }
  for (int i = 0 ; i != n; ++i)
  {
      for (int j=0 ; j != m; ++j)
      {
        acumulador += A[i][j]*v[j];
      }
      y.push_back(acumulador);
      acumulador=0.0;
  }
  return y;
}

////// matriz  por matriz: asumimos que las dimensiones son validas  //////////
doubleMatrix matrizXMatriz(doubleMatrix A, doubleMatrix B)
{
  doubleMatrix R={};
  double acumulador = 0.0;
  int n=A.size(); //filas de A
  int m=B.size(); //filas de B, columnas de A
  int r; //columnas de B

  if (A.size()>0)
  {
    m = B.size();
  }

  if (m>0)
  {
    r=B[0].size();
  }
  //calcular R[i][j]
  for (int i = 0 ; i != n; ++i)
  {
    for (int j=0 ; j != r; ++j)
    {
      for (int k=0; k<m; ++k)
      {
            acumulador += A[i][k]*B[k][j];
      }
      R[i].push_back(acumulador);
      acumulador=0.0;
    }
  }
  return R;
}

doubleMatrix vvt(doubleVector v)
{
  doubleMatrix R={};
  double acumulador = 0.0;
  int n=v.size(); //filas de A

  //calcular R[i][j]
  for (int i = 0 ; i != n; ++i)
  {
    for (int j=0 ; j != n; ++j)
    {
      acumulador += v[i]*v[j];
      R[i].push_back(acumulador);
      acumulador=0.0;
    }
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
int MetodoPotencias(doubleMatrix A, doubleVector x,int nroIter,float tol, double &autoval, doubleVector &autovec)
{
  //
  doubleVector y; // guarda el valor de la ultima iteracion
  double norma, lambda;
//  double nant=0.0;
  int indice=0; //indice del elemento que define la norma infinito
  double r=1.0;

  std::cout << "entrando a potencias: \n";

  for (int i= 0; i<x.size(); ++i) {
    std::cout << x[i]  << " ";
  }
  std::cout << std::endl;

  //normalizo el vector x
  //nx = norma2Vectorial(x);
  norma = normaInfinitoVectorial(x, indice);
  lambda = x[indice];
  x = vectorXEscalar(x, 1.0/lambda);

  for (int i= 0; i<x.size(); ++i) {
    std::cout << x[i]  << " ";
  }
  std::cout << std::endl;
  int k=0;
  while (k<nroIter && r > tol)
  {

    y = matrizXVector(A, x);
    std::cout << "despues de llamar matrizXvector: \n";
    for (int i= 0; i<y.size(); ++i) {
      std::cout << y[i]  << " ";
    }
    std::cout << std::endl;

    norma = normaInfinitoVectorial(y, indice);
    std::cout << "norma: " << norma << "\n";
    if (norma < 0.00000001)  // considero que la norma es cero, no puedo dividir por ella
    {
        lambda = 0;
        break;  //no hubo convergencia
    }
    lambda=y[indice];
    y = vectorXEscalar(y, 1/lambda);
std::cout << "y[indice] despues de normalizar: " << y[indice] << "\n";
    r = normaInfinitoVectorial(restaVectorial(x,y), indice);

    x = y;

    k++;
  }

  // analizar si hubo convergencia. Si no la hubo habria que intentar con otro x inicial
  if (r > tol)
    return 0; //no hubo convergencia
  else
  {
    autovec = x;
    autoval = lambda;
    return 1; // hubo convergencia
  }
}

//Entrada: matriz, cantidad de autovalores significativos.
//Salida: vector con autovalores, matriz de autovectores (uno por fila)
// los autovectores se almacenan por fila (ojo!!! No por columna!!!)
//PENDIENTE: definir la dimension de los parametros de salida en funcion del alfa?????????
int Deflacion(doubleMatrix A, int alfa, doubleVector &autovalores, doubleMatrix &autovectores)
{
  doubleVector x;
  double tol=0.00000001;
  int nroIter=100;
  double lambda;
  doubleVector autovec;
  long dimension=A[0].size();
  autovec.reserve(dimension);

  //averiguo autoval ppal y vector asociado
  //ir almacenando los autovalores y autovectores que se van hallando
  //repetir para A-lambda*v1*v1t

  // armar vector x inicial en funcion de la dimension de la matriz A
  //analizar opciones de como armarlo PENDIENTE
  for (int i=0; i<dimension; ++i)
    x.push_back(1);

  for (int d=0; d<dimension && d<alfa; ++d)
  {

    if (MetodoPotencias(A, x, nroIter, tol, lambda, autovec) == 1) //hubo convergencia
    {
      //Almacenar valores obtenidos para el autovalor y autovector ppal
      autovalores[d]=lambda;
      autovectores[d]=autovec;
      if (d<dimension-1)
        A = restaMatricial(A, matrizXEscalar(vvt(autovec), lambda));
    }
    else
    {
      //fallo el metodo de la potencia
      std::cout << "fallo metodo de las potencias\n";
    }
  }
}

// se calcula X*Xt. Por ahora no lo uso: se obtiene una matriz de n x n (n=cantidad de imagenes)
void CalcularCovarianza(doubleMatrix X, int filas, int columnas, doubleMatrix &mcov){
    //Xt*X
    double acumulador=0;

    //reservo espacio para la matriz de dimension filas por filas
    mcov.reserve(filas);
    for (int i=0; i<filas; i++)
      mcov[i].reserve(filas);

    for (int i=0; i<filas; i++){
      for (int j=0; j<filas; j++){
        acumulador=0.0;
        for (int k=0; k<columnas; k++)
          acumulador+=X[i][k]*X[k][j];
        mcov[i].push_back(acumulador);
      }
    }
std::cout << "antes de salir de CalcularCovarianza \n";
}



//Arma en el parametro de Salida X una matriz con las imagenes normalizadas
void ArmarMatrizX(baseDeDatos muestra, doubleVector media, int filas, int columnas, doubleMatrix &X ){
  float den;

  den=sqrt(filas-1);
  std::cout << "dentro armar X. filas, columnas, X.size, X.capacity: " << filas << " " << columnas << " " << X.size() << " " << X.capacity() << std::endl;
  for (int i=0;i<filas;i++){
    for (int j=0;j<columnas;j++){
      //X[i].push_back( ((muestra[i].getData())[j]-media[j])/den );
      X[i][j]=( ((muestra[i].getData())[j]-media[j])/den );
//copiar a mano los elementos en la fila X[i][j]=muestra...
      std::cout << "dentro armar X. despues del push. i, X.size, X[i].size, X[i].capacity: " << i << " " << X.size() << " " << (X[i]).size() << " " << X[i].capacity() << std::endl;
    }
//copiar a mano los elementos en la fila X[i][j]=muestra...
    //X.push_back(X[i]);
    std::cout << "fila i de X, size X, X[i].size(): " << i << " " << X.size() << " " << X[i].size() << std::endl;
  }
  std::cout << "saliendo de armar X \n";
}




// doubleMatrix MatrizX(baseDeDatos muestra, doubleVector media, int filas, int columnas ){
//   float den;
//   doubleMatrix X;
//   X.reserve(filas);
//   den=sqrt(filas-1);
//   for (int i=0;i<filas;i++){
//     X[i].reserve(columnas);
//     for (int j=0;j<columnas;j++){
// //      X[i*columnas+j]=(muestra[i*columnas+j]-media[j])/den;
//       X[i].push_back( (muestra[i].getData()[j]-media[j])/den );
//     }
//   }
//   return X;
// }



// Recibe como parametro la base de datos con todas las imagenes
// parametro de salida una matriz con la transformacion caracteristica de cada imagen
// columnas = cantidad de bytes por imagenes. Se puede calcular a partir de una de las imagenes cualquiera
// multiplicando ancho por alto.
void PCA (baseDeDatos muestra, doubleMatrix &mtrcar, int modo){

  int filas, columnas;

  std::cout << "dentro de PCA\n";
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
      std::cout << (double)muestra[i].getData()[j] << " ";
      media[j]+= (double)muestra[i].getData()[j];
    }
    std::cout << "\n";
  }

  std::cout << "media:\n";
  for (int j=0;j<columnas;j++){
    media[j]=media[j]/filas;
  }

  //imprimir media
  for (int j=0;j<columnas;j++){
      std::cout << media[j] << " ";
  }
  std::cout << "\n";

  doubleMatrix X;

  X.reserve(filas);
  for (int i=0;i<filas;i++)
    X[i].reserve(columnas);

  std::cout << "antes de armar matriz\n";
  ArmarMatrizX(muestra, media, filas, columnas, X);
std::cout << "despues de armar X, filas: " << filas << std::endl;
std::cout << "despues de armar X, columnas: " << columnas << std::endl;
std::cout << "despues de armar X, X.size, capacity: " << X.size() << " " << X.capacity() << std::endl;
std::cout << "despues de armar X, size[0]: " << (X[0]).size() << " " << (X[0]).capacity() << std::endl;
//imprimir X
  for (int i=0;i<filas;i++){
    std::cout << "va a imprimir fila X[i]: " << i << std::endl;
    for (int j=0;j<columnas;j++){
      std::cout << X[i][j] << " ";
    }
    std::cout <<  "\n";
  }

std::cout << "despues de imprimir X \n";
//Calcular Xt*X = Matriz de covarianza
  doubleMatrix mcov;
  std::cout << "antes de invocar CalcularCovarianza \n";
  CalcularCovarianza(X, filas, columnas, mcov);

}
