#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

// filas x columnas matrix
#define filas 10
#define columnas 10

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
int rowNum[] = {-1, 0, 0, 1 };
int colNum[] = {0, -1, 1, 0 };

// The function returns false if pt is not a valid position
bool esValido(int x, int y, int matrix[filas][columnas])
{
    return ((matrix[x][y]) and (x >= 0 and x < filas) and (y >= 0 and y < columnas));

}

// Function to print the complete path from source to destination
int printPath(vector<NODO> path)
{
    if (path.empty())
        return 0;

    int len = printPath(path[0].parent) + 1;
    cout << "(" << path[0].x << ", " << path[0].y << ") ";
    return len;
}

// Find shortest route in the matrix from source cell (x, y) to
// destination cell (filas - 1, filas - 1)
int findPath(int matrix[filas][columnas], int ox, int oy, int fx, int fy)
{
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
            int len = printPath({curr});
            return len;
        }
        //get value of current cell
        int n = matrix[i][j];
        // check all 4 possible movements from current cell
        // and recur for each valid movement
        for (int k = 0; k < 4; k++)
        {
            // get next position coordinates using value of current cell
            int x = i + rowNum[k] * n;
            int y = j + colNum[k] * n;

            // check if it is possible to go to next position
            // from current position
            if (esValido(x, y, matrix))
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
    return 0;
}

// main function
int main()
{
    int matrix[filas][columnas] =
            {
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1}

            };
    matrix[0][1] = 0;
    matrix[0][6] = 0;
    matrix[1][9] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][4] = 0;
    matrix[2][8] = 0;
    matrix[3][0] = 0;
    matrix[3][2] = 0;
    matrix[3][8] = 0;
    matrix[4][0] = 0;
    matrix[4][1] = 0;
    matrix[4][2] = 0;
    matrix[5][8] = 0;
    matrix[6][8] = 0;
    matrix[7][5] = 0;
    matrix[7][8] = 0;
    matrix[8][4] = 0;
    matrix[8][7] = 0;
    matrix[9][5] = 0;
    cout<< " ";
    for(int j = 0; j < columnas; j++)
        cout << j << " ";
    cout << endl;
    for(int i = 0; i < filas; i++){
        cout << i << " ";
        for(int j = 0; j <columnas; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }


    // Find a route in the matrix from source cell (0, 0) to
    // destination cell (filas - 1, columnas - 1)
    int len = findPath(matrix, 0, 0, 9, 9);

    if (len != -1) {
        cout << "\nShortest Path length is " << len;
    } else {
        cout << "Destination not possible";
    }

    return 0;
}
