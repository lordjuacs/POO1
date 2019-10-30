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

class Point{
public:
    int x, y;
};


//funcion para pedir origen y destino
Point pedirCoordenada(const string& palabra, int filas, int columnas){
    Point coordenada{};
    int xi, yi;
    do{
        cout << "Ingrese la posicion x del" << palabra;
        cin >> xi;
    } while((xi < 0 or xi >= filas));
    do{
        cout << "Ingrese la posicion y del" << palabra;
        cin >> yi;
    } while((yi < 0 or yi >= columnas));
    coordenada.x = xi;
    coordenada.y = yi;
    return coordenada;
}

// queue node used in BFS
struct NODO
{
    // (x, y) represents coordinates of a cell in matrix
    int x, y;
    // parent stores the parent Node of the current cell
    // It will have only one entry i.e. parent node
    vector<NODO> parent;
    // As we are using struct as a key in a std::set,
    // we need to overload below operators
    bool operator==(const NODO& ob) const
    {
        return x == ob.x && y == ob.y;
    }
    bool operator<(const NODO& ob) const
    {
        return x < ob.x || (x == ob.x && y < ob.y);
    }
};

// Below arrays details all 4 possible movements from a cell
const int rowNum[] = {-1, 0, 0, 1 };
const int colNum[] = {0, -1, 1, 0 };

// The function returns false if pt is not a valid position
bool esValido(int x, int y, int ** matrix, int filas, int columnas)
{
    return ((matrix[x][y]) and (x >= 0 and x < filas) and (y >= 0 and y < columnas));

}

// Function to print the complete path from source to destination
int imprimirCamino(vector<NODO> path, vector<Point>&coordenadasCamino)
{
    if (path.empty())
        return 0;

    int len = imprimirCamino(path[0].parent, coordenadasCamino) + 1;
    cout << "(" << path[0].x << ", " << path[0].y << ") ";
    Point coorde{};
    int equis =path[0].x;
    int lle = path[0].y;
    coorde.x = equis;
    coorde.y = lle;
    coordenadasCamino.push_back(coorde);
    return len;
}

// Find shortest route in the matrix from source cell (x, y) to
// destination cell (filas - 1, filas - 1)
int encontrarCamino(int **matrix, int filas, int columnas, Point origen, Point destino, vector<Point>coordenadasCamino)
{
    int ox = origen.x;
    int oy = origen.y;
    int fx = destino.x;
    int fy = destino.y;
    // create a queue and enqueue first node
    queue<NODO> q;
    NODO src = {ox, oy};
    q.push(src);
    // set to check if matrix cell is visited before or not
    set<NODO> visited;
    visited.insert(src);
    // run till queue is not empty
    while (!q.empty())
    {
        // pop front node from the queue and process it
        NODO curr = q.front();
        q.pop();
        int i = curr.x;
        int j = curr.y;
        // if destination is found, print the shortest path and
        // return the shortest path length
        if (matrix[i][j] && i == fx && j == fy && matrix[i][j])
        {
            cout << "Shortest path is: ";
            int len = imprimirCamino({curr}, coordenadasCamino);
            return len;
        }
        //get value of current cell
        // check all 4 possible movements from current cell
        // and recur for each valid movement
        for (int k = 0; k < 4; k++)
        {
            // get next position coordinates using value of current cell
            int x = i + rowNum[k];
            int y = j + colNum[k];

            // check if it is possible to go to next position
            // from current position
            if (esValido(x, y, matrix, filas, columnas))
            {
                // construct the next cell node
                NODO next = {x, y, {curr} };

                // if it not visited yet
                if (!visited.count(next) && matrix[next.x][next.y])
                {
                    // push it into the queue and mark it as visited
                    q.push(next);
                    visited.insert(next);
                }
            }
        }
    }

    // return -1 if path is not possible
    return -1;
}





//encontrar camino

void CaminoFinal(int **matrix, int filas, int columnas, Point origen, Point destino, vector<Point>&coordenadasCamino){
    int len = encontrarCamino(matrix, filas, columnas, origen, destino, coordenadasCamino);
    if (len != -1) {
        cout << endl;
        cout << "Casillas del camino: " << len;
    } else {
        cout << endl;
        cout << "No existe ningun camino. F.";
    }

}

//liberar espacio de memoria
void liberarMatriz(int ** &matriz, int filas){
    for(int i = 0; i < filas; i++)
        delete [] matriz[i];
    delete [] matriz;
    matriz = nullptr;
}






#endif //CODIGOBASEPOO_FUNCIONES_H


