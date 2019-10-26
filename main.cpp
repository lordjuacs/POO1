#include "funciones.h"

const string fichero = "../laberintos/laber1.txt";

int main()
{
    char ** matriz = nullptr;
    tipo_n filas, columnas, tobs;

    ifstream fi;
    fi.open(fichero);

    if(fi.is_open())
    {
        fi >> filas >> columnas;
        matriz = new char*[filas];
        for(tipo_n i = 0; i < filas; i++)
        {
            matriz[i] = new char[columnas];
        }

        for(tipo_n i = 0; i < filas; i++)
        {
            for(tipo_n j = 0; j < columnas; j++)
            {
                matriz[i][j] = ' ';
            }
        }

        fi >> tobs;
        for(tipo_n i = 0; i < tobs; i++)
        {
            tipo_n xo, xy;
            fi >> xo >> xy;
            matriz[xo][xy] = char(254);
        }
        fi.close();
    }
    else cerr << "Error de lectura" << endl;

    for(tipo_n i = 0; i < filas; i++)
    {
        for(tipo_n j = 0; j < columnas; j++)
        {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}