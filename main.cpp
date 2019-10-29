// C++ program to find the shortest path between
// a given source cell to a destination cell.
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include <deque>
using namespace std;
#define ROW 9
#define COL 10



//To store matrix cell cordinates
class Point
{
public:
    int x;
    int y;
};

// A Data Structure for queue used in BFS
class queueNode
{
public:
    Point pt;  // The cordinates of a cell
    int dist;  // cell's distance of from the source
};

void pasarQueueAtxt(vector <int> *vec){
    ofstream nuevo_archivo;
    nuevo_archivo.open("datosQueue.txt");

    for(auto elemento : *vec){
        nuevo_archivo  <<"x: "<< elemento << endl;
        //x << " y: " << elemento.pt.y  << " dist: "<< elemento.dist << endl;
    }
    nuevo_archivo.close();
}
/*void printQueue(deque<queueNode> q)
{

    //printing content of queue
    while (!q.empty()){
        nuevo_archivo <<"x: "<< q.front().pt.x << " y: " << q.front().pt.y  << " dist: "<< q.front().dist;
        q.pop_front();
        cout << endl;
    }
    // cout<<endl;
}*/



// check whether given cell (row, col) is a valid
// cell or not.
bool isValid(int row, int col)
{
    // return true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL);
}

// These arrays are used to get row and column
// numbers of 4 neighbours of a given cell
int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

// function to find the shortest path between
// a given source cell to a destination cell.
int BFS(int mat[][COL], Point src, Point dest)
{
    // check source and destination cell
    // of the matrix have value 1
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y])
        return -1;

    bool visited[ROW][COL];
    memset(visited, false, sizeof visited);

    // Mark the source cell as visited
    visited[src.x][src.y] = true;

    // Create a queue for BFS
    deque<queueNode> q;

    // Distance of source cell is 0
    queueNode s = {src, 0};
    q.push_back(s);  // Enqueue source cell

    // Do a BFS starting from source cell
    while (!q.empty()) {
        queueNode curr = q.front();
        Point pt = curr.pt;

        // If we have reached the destination cell,
        // we are done
        if (pt.x == dest.x && pt.y == dest.y)
            return curr.dist;

        // Otherwise dequeue the front cell in the queue
        // and enqueue its adjacent cells
        q.pop_front();

        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            // if adjacent cell is valid, has path and
            // not visited yet, enqueue it.
            if (isValid(row, col) && mat[row][col] &&
                !visited[row][col]) {
                // mark cell as visited and enqueue it
                visited[row][col] = true;
                queueNode Adjcell = {{row, col},
                                     curr.dist + 1};
                q.push_back(Adjcell);
            }
        }

        //printQueue(q);

        vector<int> nuevoIntX;
        nuevoIntX.reserve(q.size());
        for(auto elemento : q)
            nuevoIntX.push_back(elemento.pt.x);
        vector<int> *pIntX = &nuevoIntX;
        pasarQueueAtxt(pIntX);
    }







    // Return -1 if destination cannot be reached
    return -1;
}

// Driver program to test above function
int main()
{
    int mat[ROW][COL] =
            {
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
                    { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
            };

    Point source = {0, 0};
    Point dest = {8, 1};
    int dist = BFS(mat, source, dest);
    if (dist != INT_MAX)
        cout << "Shortest Path is " << dist + 1;
    else
        cout << "Shortest Path doesn't exist";


    return 0;
}