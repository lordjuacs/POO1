#include "funciones.h"

const string fichero = "../laberintos/laber1.txt";

int main()
{
    int ** matriz = nullptr;
    tipo_n filas = 0, columnas = 0, tobs = 0;
    txtAMatriz(matriz, fichero, filas, columnas, tobs);
    for (int x=0; x<filas;x++){
        if(x==0){
            cout<<"   0   1   2   3   4   5   6   7   8   9"<<endl;
        }cout<<x<<" ";
        for(int y=0;y<columnas;y++){

            if(matriz[x][y]==0){
                cout<<"[*] ";
            }
            else{
                cout<<"[ ] ";

            }

        }cout<<endl;
    }
    Point origen = pedirCoordenada("origen", filas, columnas);
    Point destino = pedirCoordenada("destino", filas, columnas);
    vector<Tupla> Previo;
    stack<node> OpcionCamino;

    //distancia minima desde el origen hasta el final (contando el origen y el final)
    int distancia = BFS(matriz, filas, columnas, origen, destino, Previo);
    vector<Point> Final = CaminoFinal(matriz, filas, columnas, origen, destino, distancia, OpcionCamino);
    actualizarMatriz(matriz, filas, columnas, Final);
    //solo falta implementar la funcion que imprima "bonito", con chars.
    liberarMatriz(matriz, filas, columnas);

    return 0;
}
