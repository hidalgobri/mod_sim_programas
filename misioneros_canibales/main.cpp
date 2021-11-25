#include <iostream>
#include <bits/stdc++.h>

const int FILAS_MATRIZ_POSIB = 5;
const int COLUMNAS_MATRIZ_POSIB = 3;

//matrices con todas las opciones posibles
//cuando el barco es 0 --> esta en b
//como queda a, cuando el barco se

int posibilidades_ab[5][3] = {{0,-1,-1} //misionero, canibal, barco
                        , {0,-2,-1}
                        , {-1,0,-1}
                        , {-2,0,-1}
                        , {-1,-1,-1}};
//como queda a
int posibilidades_ba[5][3] = {{0,1,1}
                            ,{0,2,1}
                            ,{1,0,1}
                            ,{2,0,1}
                            ,{1,1,1}};

struct Node
{
    int misioneros;
    int canibales;
    int barco;
    std::vector<Node *>child;
};

Node *newNode(int misioneros, int canibales, int barco)
{
    Node *temp = new Node;

    temp->misioneros = misioneros;
    temp->canibales = canibales;
    temp->barco = barco;

    return temp;
}

int *opciones_nodos_hijos(Node *padre) //verifica que opciones de todas las posibles, cumplen con la condición
{

    static int hijos[5] = {-1,-1,-1,-1,-1};
    int contador_hijos = 0;

    if (padre->barco == 0) //el barco esta en b
    {
        for (int i = 0; i < FILAS_MATRIZ_POSIB ; i++) //recorro las columnas
        {
            int misioneros_actual = padre->misioneros - posibilidades_ab[i][0];
            int canibales_actual = padre->canibales - posibilidades_ab[i][1];

            if(misioneros_actual >= 0 && misioneros_actual <= 3 && canibales_actual >= 0 && canibales_actual <= 3)
            {
                if( misioneros_actual >= canibales_actual && ((3 - misioneros_actual) >= (3 - canibales_actual ) || (3 -  misioneros_actual) == 0 ))// condición del lado a && condición del lado b
                {
                   //std::cout<<"posible hijo "<<i;
                   hijos[contador_hijos] = i;
                   contador_hijos ++;
                }
            }
        }
    }
        else if(padre->barco == 1) // el barco esta en a
    {
        std::cout<<"entró barco 1 \n";

        for (int j = 0; j < FILAS_MATRIZ_POSIB ; j++) //recorro las columnas
        {
            int misioneros_actual = padre->misioneros + posibilidades_ab[j][0];
            int canibales_actual = padre->canibales + posibilidades_ab[j][1];

           // count<<"posible hijo-->"<<i<<endl;

            if(misioneros_actual >= 0 && misioneros_actual <= 3 && canibales_actual >= 0 && canibales_actual <= 3)
            {
                //std::cout<<"m"<<misioneros_actual <<"c"<< canibales_actual <<"\n";

                if( misioneros_actual >= canibales_actual && ((3 - misioneros_actual) >= (3 - canibales_actual ) || (3 -  misioneros_actual) == 0 ))// condición del lado a && condición del lado b
                {
                   //std::cout<<"posible hijo--> "<<j<<std::endl;
                   hijos[contador_hijos] = j;
                   contador_hijos ++;
                }
            }
        }
    }


    return hijos;
}

int main()
{

    //Creo el nodo padre con el estado inicial M3C3B1
    Node *root = newNode(3 ,3 ,1);

    int *opciones_hijos = opciones_nodos_hijos(root);

    std::cout<<"hello vale, las respuestas: "<<opciones_hijos[0]<<std::endl;

    for(int y=0;y<5;y++)  // loop for the three elements on the line
    {
        std::cout<<"hello vale, las respuestas: "<<opciones_hijos[y]<<std::endl;
    }

    return 0;
}
