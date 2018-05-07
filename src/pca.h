typedef std::vector<Imagen> baseDeDatos; //matriz de Imagenes: id, ancho, alto y bytes de cada imagen
typedef std::vector<double> doubleVector;
typedef std::vector<doubleVector> doubleMatrix; //matriz para deflacion

double norma2Vectorial(doubleVector v);
double normaInfinitoVectorial(doubleVector v, int &indice);

// matriz y vectores no vacios
doubleVector matrizXVector(doubleMatrix A, doubleVector v);

doubleMatrix matrizXEscalar(doubleMatrix A, double esc);

doubleVector vectorXEscalar(doubleVector v, double esc);

// ver si hay que normalizar Ax
// iterar hasta   que en dos iteraciones sucesivas la siferencia entre las normas sea menor que la tolerancia
// si se normaliza el vector al mismo tiempo se calcula el autovalor dominante

//normalizado
int MetodoPotencias(doubleMatrix A, doubleVector x,int nroIter,float tol, double &autoval, doubleVector &autovec);

// se calcula X*Xt. Por ahora no lo uso: se obtiene una matriz de n x n (n=cantidad de imagenes)
void CalcularCovarianza(doubleMatrix X, int filas, int columnas, doubleMatrix &mcov);

//Arma en el parametro de Salida X una matriz con las imagenes normalizadas
void ArmarMatrizX(baseDeDatos muestra, doubleVector media, int filas, int columnas, doubleMatrix &X );

doubleMatrix MatrizX(baseDeDatos muestra, doubleVector media, int filas, int columnas );

void PCA (baseDeDatos muestra, doubleMatrix &mtrcar, int modo);
