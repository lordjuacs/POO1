#include "funciones.h"

int main()
{
    string fichero = pedirArchivo();
    char op = '2';
    do {
        if (op == '1')
            string fichero = pedirArchivo();

        tipo_n filas = 0, columnas = 0, tobs = 0;
        vector<Point> obstaculos;
        vector<Point> nuevosPuntos;

        txtAMatrizVector(fichero, filas, columnas, tobs, obstaculos);

        Point origen = pedirCoordenada("origen", filas, columnas);
        Point destino = pedirCoordenada("destino", filas, columnas);
        int ox = origen.x;
        int oy = origen.y;
        int fx = destino.x;
        int fy = destino.y;

        CaminoFinal(filas, columnas, ox, oy, fx, fy, obstaculos, nuevosPuntos);
        int ** matriz = nullptr;
        llenarMatriz(matriz, filas, columnas, obstaculos, nuevosPuntos);
        char ** arena = nullptr;
        matrizChar(arena, matriz, filas, columnas);
        imprimirMatriz<char **>(arena, filas, columnas);

        liberarMatriz<int **>(matriz, filas);
        liberarMatriz<char **>(arena, filas);

        op = menu();
    } while (op != '3');

    return 0;
}
