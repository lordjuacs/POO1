#include "funciones.h"

const string fichero = "../laberintos/laber1.txt";

int main()
{
    int ** matriz = nullptr;
    tipo_n filas = 0, columnas = 0, tobs = 0;
    txtAMatriz(matriz, fichero, filas, columnas, tobs);
    Point origen = pedirCoordenada("origen", filas, columnas);
    Point destino = pedirCoordenada("destino", filas, columnas);
    vector<Point>nuevosPuntos;
    CaminoFinal(matriz, filas, columnas, origen, destino, nuevosPuntos);
    liberarMatriz(matriz, filas);

    return 0;
}