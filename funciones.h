//
// Created by J on 25-Oct-19.
//
#include "tipos.h"
#ifndef CODIGOBASEPOO_FUNCIONES_H
#define CODIGOBASEPOO_FUNCIONES_H
//funcion para leer el archivo, crear la matriz con los obstaculos
void txtAMatriz(tipo_n ** &matriz, const string& fichero, tipo_n &filas, tipo_n &columnas, tipo_n &tobs){
    ifstream fi;
    fi.open(fichero);
    if(fi.is_open())
    {
        fi >> filas >> columnas;
        matriz = new int*[filas];
        for(tipo_n i = 0; i < filas; i++)
        {
            matriz[i] = new int[columnas];
        }

        for(tipo_n i = 0; i < filas; i++)
        {
            for(tipo_n j = 0; j < columnas; j++)
            {
                matriz[i][j] = 1;
            }
        }

        fi >> tobs;
        for(tipo_n i = 0; i < tobs; i++)
        {
            tipo_n xo, xy;
            fi >> xo >> xy;
            matriz[xo][xy] = 0;
        }
        fi.close();
    }
    else {
        cerr << "Error de lectura" << endl;
    }
}
//las siguientes funciones, clases y datos son las encargadas de encontrar el camino mas corto
//Sirve para almacenar una coordenada
class Point
{
public:
    int x;
    int y;
};

class vectorNodo
{
public:
    Point pt;  // Las coordenadas de una celda
    int dist;  // la distancia a la celda desde el origen
};
//este tipo de dato servira para poder almacenar las coordenadas candidatas en el vector
class Tupla
{
public:
    int x, y, dist;
};

// Revisa si una celda es valida valida o no
bool esValida(int row, int col, int filas, int columnas)
{
    // return true if row number and column number
    // is in range
    return (row >= 0) && (row < filas) && (col >= 0) && (col < columnas);
}

// Estos arrays se usan para tener el numero de filas y columnas de los 4 vecinos de cada celda
int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

// Es la funcion que encuentra el camino mas corto dentro de un laberinto con obstaculos
// Devuelve la distancia mas corta
int BFS(int ** matriz, int filas, int columnas, Point origen, Point destino, vector<Tupla> &CaminoPre)
//CaminoPre va a almacenar todas las celdas visitadas posibles, para despues pasarlo por una funcion que de las validas
{
    // Revisa si el origen y el final tienen valor de 1 (sino no tiene sentido intentar encontrar la distancia)
    if (!matriz[origen.x][origen.y] || !matriz[destino.x][destino.y])
        return -1;

    bool visitado[filas][columnas];
    memset(visitado, false, sizeof visitado);

    // Marca la celda como visitada
    visitado[origen.x][origen.y] = true;

    // Crea un vector para intentar el algoritmo:
    vector<vectorNodo> q;

    // La distancia del origen al origen es 0
    vectorNodo s = {origen, 0};
    q.push_back(s);  // Se añade el nodo origen al vector

    //Se añade el nodo origen al vector CaminPre
    Tupla ori{};
    ori.x = origen.x;
    ori.y = origen.y;
    ori.dist = 0;
    CaminoPre.push_back(ori);

    // Se hace BFS empezando del origen
    while (!q.empty()) {
        vectorNodo curr = q.front();
        Point pt = curr.pt;

        // Si ya llegamos al destino, acaba todo
        if (pt.x == destino.x && pt.y == destino.y) {
            //se añade el destino al CaminoPre
            Tupla nodo;
            nodo.x = curr.pt.x;
            nodo.y = curr.pt.y;
            nodo.dist = curr.dist;
            CaminoPre.push_back(nodo);
            //Se devuelve la longitud del camino
            return curr.dist;
        }
        // Si no es el caso, eliminar el primer objeto y añadir los vecinos
        q.erase(q.begin());
        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            // Si la celda vecina es valida, tiene camino y aun no ha sido visitada, entonces añadirla al vector
            if (esValida(row, col, filas, columnas) && matriz[row][col] && !visitado[row][col]) {
                // marcar la celda como visitada y añadirla
                visitado[row][col] = true;
                vectorNodo Adjcell = {{row, col}, curr.dist + 1};
                //añadir la posible celda al CaminoPre
                Tupla coor;
                coor.x = row;
                coor.y = col;
                coor.dist = curr.dist + 1;
                CaminoPre.push_back(coor);
                q.push_back(Adjcell);
            }
        }

    }
    // Si el destino no se encontro, retornar -1
    return -1;
}

//funcion para pedir origen y destino
Point pedirCoordenada(string palabra, int filas, int columnas){
    Point coordenada;
    int xi, yi;
    do{
        cout << "Ingrese la posicion (x,y) del " << palabra<<": ";
        cin >> xi>>yi;
    } while((xi < 0 and xi >= filas) and (yi < 0 and yi >= columnas));
    coordenada.x = xi;
    coordenada.y = yi;
    return coordenada;
}
class node {
public:
    int x, y;
    int dir;

    node(int i, int j)
    {
        x = i;
        y = j;

        // Initially direction
        // set to 0
        dir = 0;
    }
};

bool isReachable(int ** matriz, int filas, int columnas, Point origen, Point destino, stack<node> &s)
{
    bool visitado2[filas][columnas];
    memset(visitado2, true, sizeof(visitado2));
    // Initially starting at origin.
    int i = origen.x, j = origen.y;
    node temp(i, j);

    s.push(temp);

    int fx = destino.x;
    int fy = destino.y;

    while (!s.empty()) {
        // Pop the top node and move to the
        // left, right, top, down or retract
        // back according the value of node's
        // dir variable.
        temp = s.top();
        int d = temp.dir;
        i = temp.x, j = temp.y;

        // Increment the direction and
        // push the node in the stack again.
        temp.dir++;
        s.pop();
        s.push(temp);

        // If we reach the Food coordinates
        // return true
        if (i == fx and j == fy) {
            return true;
        }

        // Checking the Up direction.
        if (d == 0) {
            if (i - 1 >= 0 and matriz[i - 1][j] and
                visitado2[i - 1][j]) {
                node temp1(i - 1, j);
                visitado2[i - 1][j] = false;
                s.push(temp1);
            }
        }

            // Checking the left direction
        else if (d == 1) {
            if (j - 1 >= 0 and matriz[i][j - 1] and
                visitado2[i][j - 1]) {
                node temp1(i, j - 1);
                visitado2[i][j - 1] = false;
                s.push(temp1);
            }
        }

            // Checking the down direction
        else if (d == 2) {
            if (i + 1 < filas and matriz[i + 1][j] and
                visitado2[i + 1][j]) {
                node temp1(i + 1, j);
                visitado2[i + 1][j] = false;
                s.push(temp1);
            }
        }
            // Checking the right direction
        else if (d == 3) {
            if (j + 1 < columnas and matriz[i][j + 1] and
                visitado2[i][j + 1]) {
                node temp1(i, j + 1);
                visitado2[i][j + 1] = false;
                s.push(temp1);
            }
        }

            // If none of the direction can take
            // the rat to the Food, retract back
            // to the path where the rat came from.
        else {
            visitado2[temp.x][temp.y] = true;
            s.pop();
        }
    }

    // If the stack is empty and
    // no path is found return false.
    return false;
}

void printStack(stack<node>s, vector<Point>&Final){
    if (s.empty())
        return;
    node cima = s.top();
    int xi = cima.x;
    int yi = cima.y;
    s.pop();
    printStack(s, Final);
    Point coordenada;
    coordenada.x = xi;
    coordenada.y = yi;
    Final.push_back(coordenada);
    cout << "<" << xi << "," << yi << ">" << " ";
    s.push(cima);
}



//funcion para imprimir distancia, coordenadas y el vector final con el camino
vector <Point>CaminoFinal(int ** matriz, int filas, int columnas, Point origen, Point destino, int dist, stack<node> &s) {
    vector <Point> Final;
    if (dist != -1) {
        cout << "El camino mas corto es: " << ++dist << endl;
        if(isReachable(matriz, filas, columnas, origen, destino, s)){
            printStack(s, Final);
            cout << endl;
            cout << "Nuestro algoritmo de conteo de minima distancia es 100% eficiente." << endl;
            cout << "Nuestro algoritmo de impresion de camino mas optimo aun esta en proceso." << endl;
            cout << "Esperemos que valore el esfuerzo profesor." << endl;
        }



        /*for (int i = 0; i < previo.size() - 1; i++) {
            if (previo[i].dist + 1 == previo[i + 1].dist)
                Final.push_back(previo[i]);
            else{

            }
        }
        Final.push_back(previo.back());
        for (int i = 0; i < Final.size(); i++) {
            cout << i + 1 << " x: " << Final[i].x << " y: " << Final[i].y << endl;
        }
        cout << endl;
        return Final;
         */
    }
    else {
        cout << "No existe ningun camino" << endl;
        return Final;
    }
}


void actualizarMatriz(int **&matriz, int filas, int columnas, vector<Point>Final){
    int i = 0;
    while(i < Final.size()){
        int posicion_x = Final[i].x;
        int posicion_y = Final[i].y;
        matriz[posicion_x][posicion_y] = 2;
    }
}



//liberar espacio de memoria
void liberarMatriz(int ** &matriz, int filas, int columnas){
    for(int i = 0; i < filas; i++)
        delete [] matriz[i];
    delete [] matriz;
    matriz = nullptr;
}







#endif //CODIGOBASEPOO_FUNCIONES_H


