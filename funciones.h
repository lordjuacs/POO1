//
// Created by J on 25-Oct-19.
//
#include "tipos.h"
#ifndef CODIGOBASEPOO_FUNCIONES_H
#define CODIGOBASEPOO_FUNCIONES_H

char menu(){
    char opcion;
    cout<<"--------------------------\n";
    cout<<"1- Seleccionar archivo\n";
    cout<<"2- Seleccionar coordenadas\n";
    cout<<"3- Salir\n";
    cout<<"Elija opcion (1-3):";
    cin>>opcion;
    cout<<endl;
    return opcion;
}

string pedirArchivo() {
    string file;
    cout << "Ingrese nombre del archivo: "; cin >> file;
    string fichero = "../laberintos/" + file;
    return fichero;
}

class Point{
public:
    int x, y;
    Point(){
        x = 0;
        y = 0;
    };
    Point(int _x, int _y){
        x = _x;
        y = _y;
    }
};
void llenarMatriz(int **&matriz, int filas, int columnas, vector <Point>&obstaculos,  vector <Point>&coordenadas){
    matriz = new int*[filas];
    for(int i = 0; i < filas; i++){
        matriz[i] = new int[columnas];
    }

    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = 1;
        }
    }

    for(auto elemento:obstaculos)
        matriz[elemento.x][elemento.y] = 0;
    for(auto cosa:coordenadas)
        matriz[cosa.x][cosa.y] = 2;
}

void matrizChar(char ** &arena, int **&matriz, int filas, int columnas){
    arena = new char*[filas];
    for(int i = 0; i < filas; i++){
        arena[i] = new char[columnas];
    }

    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(matriz[i][j] == 1)
                arena[i][j] = ' ';
            else if(matriz[i][j] == 2)
                arena[i][j] = '*';
            else
                arena[i][j] = char(254);
        }
    }
}

//funcion para leer el archivo, crear la matriz con los obstaculos
void txtAMatrizVector(const string& fichero, tipo_n &fil, tipo_n &col, tipo_n &tobs, vector <Point>&obstaculos)
{
    ifstream fi;
    fi.open(fichero);
    if(fi.is_open()) {
        fi >> fil >> col;
        fi >> tobs;
        for(tipo_n i = 0; i < tobs; i++)
        {
            tipo_n xo, xy;
            fi >> xo >> xy;
            Point obs(xo, xy);
            obstaculos.push_back(obs);
        }
        fi.close();

    }
    else {
        cerr << "Error de lectura" << endl;
    }
}




//funcion para pedir origen y destino
Point pedirCoordenada(const string& palabra, int filas, int columnas){
    Point coordenada{};
    int xi, yi;
    do{
        cout << "Ingrese las coordenadas de " << palabra << ":";
        cin >> xi >> yi;
    } while(xi < 0 or xi >= filas or yi < 0 or yi >= columnas);

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
bool esValido(int x, int y, const vector<Point>&obstaculos, int filas, int columnas)
{
    int matrix[filas][columnas];
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matrix[i][j] = 1;
        }
    }
    for(auto elemento : obstaculos)
        matrix[elemento.x][elemento.y] = 0;
    return matrix[x][y] and (x >= 0 and x < filas) and (y >= 0 and y < columnas);
}

// Function to print the complete path from source to destination
int imprimirCamino(vector<NODO> path, vector<Point>&coordenadas)
{
    if (path.empty())
        return 0;

    int len = imprimirCamino(path[0].parent, coordenadas) + 1;
    cout << "(" << path[0].x << ", " << path[0].y << ") ";
    Point coor(path[0].x, path[0].y);
    coordenadas.push_back(coor);
    return len;
}

// Find shortest route in the matrix from source cell (x, y) to
// destination cell (filas - 1, filas - 1)
int encontrarCamino(const int filas, const int columnas, const int ox, const int oy, const int fx, const int fy, const vector<Point>&obstaculos, vector<Point>&coordenadas)
{
    int matrix[filas][columnas];
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matrix[i][j] = 1;
        }
    }
    for(auto elemento : obstaculos)
        matrix[elemento.x][elemento.y] = 0;
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
        if ((matrix[i][j]) && (i == fx) && (j == fy) )
        {
            cout << "CON HEURISTICA:" << endl;
            cout << "--------------------------" << endl;
            int len = imprimirCamino({curr}, coordenadas);

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
            if (esValido(x, y, obstaculos, filas, columnas))
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

void CaminoFinal(const int filas, const int columnas, const int ox, const int oy, const int fx, int fy, const vector<Point>&obstaculos, vector<Point>&coordenadas){
    int len = encontrarCamino(filas, columnas, ox, oy, fx, fy, obstaculos, coordenadas);
    if (len != -1) {
        cout << endl;
        cout << "Casillas del camino: " << len << endl;
    }
    else {
        cout << endl;
        cout << "No existe ningun camino. F.";
    }

}
template<typename T>void imprimirMatriz(T &matrix, int filas, int columnas){
    cout << endl;
    cout << "    ";
    for(int j = 0; j < columnas; j++)
        cout << " " << j << " ";
    cout << endl;
    for(int i = 0; i < filas; i++){
        cout << "  " << i << " ";
        for(int j = 0; j < columnas; j++){
            cout << '[' << matrix[i][j] << ']';
        }
        cout << endl;
    }
}



//liberar espacio de memoria
template<typename T>void liberarMatriz(T  &matrix, int filas){
    for(int i = 0; i < filas; i++)
        delete [] matrix[i];
    delete [] matrix;
    matrix = nullptr;
}





#endif //CODIGOBASEPOO_FUNCIONES_H



