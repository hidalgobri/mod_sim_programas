#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

const int FILAS_MATRIZ_POSIB = 5;
const int COLUMNAS_MATRIZ_POSIB = 3;

int total_nodos = 0;
//matrices con todas las opciones posibles

//cuando el barco es 0 --> esta en b

//como queda a, cuando el barco viaja de A a B

int posibilidades_ab[5][3] = {{0,-1,-1} //misionero, canibal, barco
                        , {0,-2,-1}
                        , {-1,0,-1}
                        , {-2,0,-1}
                        , {-1,-1,-1}};

//como queda a, cuando el barco viaja de B a A
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

// Prints the n-ary tree level wise
void levelOrderTraversal(Node * root)
{
    if (root==NULL)
        return;

    // Standard level order traversal code
    // using queue
    std::queue<Node *> q;  // Create a queue
    q.push(root); // Enqueue root
    while (!q.empty())
    {
        int n = q.size();

        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            Node * p = q.front();
            q.pop();
            std::cout << "M"<<p->misioneros << " C"<<p->canibales<<" B"<<p->barco<<"  ||  " ;

            // Enqueue all children of the dequeued item
            for (int i=0; i<p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }

        std::cout << std::endl; // Print new line between two levels
    }
}

//función condicion
int *opciones_nodos_hijos(Node *padre) //verifica que opciones de todas las posibles, cumplen con la condición
{

    static int hijos[5] = {-1,-1,-1,-1,-1};
    int contador_hijos = 0;

    if (padre->barco == 0) //el barco esta en b
    {
        for (int i = 0; i < FILAS_MATRIZ_POSIB ; i++) //recorro las columnas
        {
            int misioneros_actual = padre->misioneros + posibilidades_ab[i][0];
            int canibales_actual = padre->canibales + posibilidades_ab[i][1];

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


//padre viene ya con un primer nivel
Node *crea_arbol( Node *padre, int cant_nodos_ult_nivel )
{

    bool hay_nuevo_nivel = true;
    int num_nodos_ult_nivel = cant_nodos_ult_nivel;
    //std::cout<<"num_nodos_ult_nivel------"<< num_nodos_ult_nivel<<"\n";
    while( hay_nuevo_nivel )
    {
        std::cout<<"hay nuevo nivel\n";
        int bandera_nuevo_nivel = 0;

        std::cout<< "valor que empieza i "<<abs(total_nodos-num_nodos_ult_nivel) + 1<<"\n";

        for ( int i = abs(total_nodos-num_nodos_ult_nivel) + 1  ; i < total_nodos ; i++ )
        {
            std::cout<<"recorriendo ultimo nivel de nodos" << i <<"\n";

            int *opciones_hijos = opciones_nodos_hijos(padre->child[i]); //caminos posibles a los que se puede ir que cumplen con la funcion condicion

            for (int j = 0 ; j < 5 ; j++)
            {
                if(opciones_hijos[j] != -1)
                {
                    bandera_nuevo_nivel ++;

                    int actual_misioneros = padre->child[i]->misioneros+posibilidades_ab[j][0];
                    int actual_canibales = padre->child[i]->canibales+posibilidades_ab[j][1];
                    int actual_barco = padre->child[i]->barco + posibilidades_ab[j][2];

                    (padre->child[j]->child).push_back(newNode(actual_misioneros,actual_canibales,actual_barco));


                }
            }
        }

        if(bandera_nuevo_nivel > 0)
        {
            hay_nuevo_nivel = true;

        } else {

            hay_nuevo_nivel = false;
        }

        std::cout<<"v a l e r i a";
        total_nodos += total_nodos + bandera_nuevo_nivel;
        num_nodos_ult_nivel = bandera_nuevo_nivel;
        std::cout<<"---------------->total_nodos-num_nodos_ult_nivel"<<total_nodos-num_nodos_ult_nivel<<"\n";


    }

    return padre;

}

int main()
{
    //Creo el nodo padre con el estado inicial M3C3B1
    Node *root = newNode(3 ,3 ,1);

    int *opciones_hijos = opciones_nodos_hijos(root);

    int numero_hijos = 0;
    //-------------------creo el primero nivel
    for (int i = 0 ; i < 5 ; i++)
    {
        if(opciones_hijos[i] != -1)
        {
            numero_hijos++;

            int actual_misioneros = root->misioneros+posibilidades_ab[i][0];
            int actual_canibales = root->canibales+posibilidades_ab[i][1];
            int actual_barco = root->barco + posibilidades_ab[i][2];

            (root->child).push_back(newNode(actual_misioneros,actual_canibales,actual_barco));


        }
    }

    std::cout<<"numero de hijos nivel 1 "<< numero_hijos <<"\n";

    Node *arbol_completo = crea_arbol(root, numero_hijos);
    //-------------------

    std::cout<< "hello brigitte, la respuesta: \n";
    levelOrderTraversal(arbol_completo);


    return 0;
}
