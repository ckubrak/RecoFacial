typedef std::vector<Imagen> baseDeDatos; //matriz de Imagenes: id, ancho, alto y bytes de cada imagen
typedef std::vector<double> dvector;
typedef std::vector<dvector> dmatriz; //matriz para deflacion

double norma2Vectorial(dvector v);
double normaInfinitoVectorial(dvector v, int &indice);

// matriz y vectores no vacios
dvector matrizXVector(dmatriz A, dvector v);

dmatriz matrizXEscalar(dmatriz A, double esc);

dvector vectorXEscalar(dvector v, double esc);

// ver si hay que normalizar Ax
// iterar hasta   que en dos iteraciones sucesivas la siferencia entre las normas sea menor que la tolerancia
// si se normaliza el vector al mismo tiempo se calcula el autovalor dominante

//normalizado
int MetodoPotencias(dmatriz A, dvector x,int nroIter,float tol, double &autoval, dvector &autovec);

// se calcula X*Xt. Por ahora no lo uso: se obtiene una matriz de n x n (n=cantidad de imagenes)
void CalcularCovarianza(dmatriz X, int filas, int columnas, dmatriz &mcov);

//Arma en el parametro de Salida X una matriz con las imagenes normalizadas
void ArmarMatrizX(baseDeDatos muestra, dvector media, int filas, int columnas, dmatriz &X );

dmatriz MatrizX(baseDeDatos muestra, dvector media, int filas, int columnas );

void PCA (baseDeDatos muestra, dmatriz &mtrcar, int modo);
