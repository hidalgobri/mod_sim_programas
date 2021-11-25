#include <iostream>
#include <bits/stdc++.h>
//hola
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
    std::cout<<"entró funcion nodos";
    int hijos[5] = {0,0,0,0,0};
    int contador_hijos = 0;

    if (padre->barco == 0) //el barco esta en b
    {

        std::cout<<"entró barco 0";
        for (int i = 0; i < sizeof(posibilidades_ab) ; i++) //recorro las columnas
        {
            std::cout<<"posible hijo-->"<<i<<std::endl;
            /*
            int misioneros_actual = padre->misioneros - posibilidades_ab[i][0];
            int canibales_actual = padre->canibales - posibilidades_ab[i][1];

            if(misioneros_actual >= 0 && misioneros_actual <= 3 && canibales_actual >= 0 && canibales_actual <= 3)
            {
                if( misioneros_actual >= canibales_actual && (3 - ( misioneros_actual) >= (3 - (canibales_actual) ) ))// condición del lado a && condición del lado b
                {
                cout<<"posible hijo "<<i;
                   hijos[contador_hijos] = i;
                   contador_hijos ++;
                }
            }

            */
        }

    }
        else if(padre->barco == 1) // el barco esta en a
    {
        std::cout<<"entró barco 1";
        for (int j = 0; j < sizeof(posibilidades_ab) ; j++) //recorro las columnas
        {
            std::cout<<"posible hijo-->"<<j<<std::endl;
             /*
            int misioneros_actual = padre->misioneros + posibilidades_ab[j][0];
            int canibales_actual = padre->canibales + posibilidades_ab[j][1];

           // count<<"posible hijo-->"<<i<<endl;

            if(misioneros_actual >= 0 && misioneros_actual <= 3 && canibales_actual >= 0 && canibales_actual <= 3)
            {
                if( misioneros_actual >= canibales_actual && (3 - ( misioneros_actual) >= (3 - (canibales_actual) ) )) // condición del lado a && condición del lado b
                {
                    count<<"posible hijo-->"<<i;
                   hijos[contador_hijos] = i;
                   contador_hijos ++;
                }
            }
*/
        }
    }
    return hijos;
}

int main()
{

    //Creo el nodo padre con el estado inicial M3C3B1
    Node *root = newNode(3 ,3 ,1);

    int *opciones_hijos = opciones_nodos_hijos(root);



    for(int y=0;y<sizeof(opciones_hijos);y++)  // loop for the three elements on the line
    {

        std::cout<<opciones_hijos[y]<<std::endl;  // display the current element out of the array
    }

    return 0;
}
