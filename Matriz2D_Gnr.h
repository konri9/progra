#ifndef MATRIZ2D_GNR_H
#define MATRIZ2D_GNR_H

#ifndef NULL
#define NULL 0
#endif // NULL

#include <iostream>
#include <stdlib.h>
#include <random>
using namespace std;

template <typename V>
class Matriz2D_Gnr
{
public:
    //REQ: Que se envien los parametros correspondientes
    //EFE: Construye una matriz de int
    Matriz2D_Gnr(int a, int b);

    //EFE: construye una copia de la matriz
    Matriz2D_Gnr(const Matriz2D_Gnr<V>& mat);

    ~Matriz2D_Gnr();

    //Obtiene el valor en una posicion especifica de una matriz
    V obtenerValor(int f, int c);//, V m [][]);

    void asignarValor(int f, int c, V valor);

    //REQ: Que la matriz ya se haya construido
    //EFE: retorna el valor de la posicion en la entrada [][] de la matriz
    V operator [] (const Matriz2D_Gnr<V>& mat) const;

    //REQ: que la matriz este bien construida
    //EFE: retorna true si las matrices son iguales
    Matriz2D_Gnr operator = (const Matriz2D_Gnr<V>& mat)const;

    //REQ: que las matrices esten bien construidas
    //EFE: suma dos matrices
    Matriz2D_Gnr operator + (const Matriz2D_Gnr<V>& mat);

    //REQ: que las matrices esten bien construidas
    //EFE: multiplica dos matrices
    Matriz2D_Gnr operator * (const Matriz2D_Gnr<V>& mat);

    //REQ: que las matrices esten bien construidas
    //EFE: saca el modulo entre las dos matrices
    Matriz2D_Gnr operator % (int modulin);

    //REQ: que la matriz este bien construida
    //EFE: transpone la matriz
    void transpuesta();

    //REQ: que la matriz este bien construida
    //EFE: obtiene el valor en una entrada especifica de *this
    V obtVal(int i, int j, V** e);

protected:
private:
    const int x, y;
    V** matriz;
};


template <typename V>
Matriz2D_Gnr<V>::Matriz2D_Gnr(int a, int b ): x(a), y(b)
{
    matriz = new V*[x];//[y];
    for(int i = 0; i < x; i++)
            matriz[i] = new V[y];
    //Rellena la matriz con numeros al azar
    int random = (rand() / RAND_MAX) % 10;
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            matriz[i][j] = random;
            random = (rand() / RAND_MAX) % 10;
        }
    }
    //ctor int
}


template<typename V>
V Matriz2D_Gnr<V>::obtVal(int f, int c, V** e)//, //V matrix)
{
    V res = this->matriz[f][c];
    return res;
}

template<typename V>
void Matriz2D_Gnr<V>::asignarValor(int f, int c, V valor)
{
    this->matriz[f][c] = valor;
}


//tendria que ser algo como res.asignar(i, j, valordelaotramatrizenlaposicionij);

template <typename V>
Matriz2D_Gnr<V>::Matriz2D_Gnr(const Matriz2D_Gnr<V>& mat): x(mat.x), y(mat.y)
{
    //ctor de copias
}


template <typename V>
Matriz2D_Gnr<V>::~Matriz2D_Gnr()
{
    if(this->matriz != NULL) delete [] matriz;

}

template <typename V>
Matriz2D_Gnr <V> Matriz2D_Gnr <V> ::operator=(const Matriz2D_Gnr<V>& mat) const
{
    Matriz2D_Gnr<V> res(mat.x,mat.y);
    for(int i=0; i<mat.x; i++)
    {
        for(int j=0; j<mat.y; j++)
        {
            res.matriz[i][j] = mat.matriz[i][j];
        }
    }
    return res;
}


template <typename V>
Matriz2D_Gnr<V> Matriz2D_Gnr <V>::operator+(const Matriz2D_Gnr<V>& mat)
{
    if(this->x != mat.x || this->y != mat.y) throw -1;
    Matriz2D_Gnr<V> res(mat.x,mat.y);
    for(int i=0; i<mat.x; i++)
    {
        for(int j=0; j<mat.y; j++)
        {
            V temp = mat.matriz[i][j];
            res.matriz[i][j] = mat.matriz[i][j];// + this->matriz [i][j];//obtVal(i,j);
        }
    }
    return res;
}

template <typename V>
Matriz2D_Gnr<V> Matriz2D_Gnr<V>:: operator*(const Matriz2D_Gnr<V>& mat)// throw -1
{
    if(this->y != mat.x) throw -1; // la matriz no es multiplicable
    Matriz2D_Gnr<V> res(this->x,mat.y); //toma las nuevas dimensiones
    for(int i=0; i<this->x; i++)
    {
        V suma=0;
        for(int j=0; j<mat.y; j++)
        {
            for(int k=0; k<this->y; k++)
            {
                suma += mat.matriz[i][j] * this->matriz[i][j];
            }
        }
        suma = 0; // reinicia la suma
    }
    return res;
}

template <typename V>
Matriz2D_Gnr<V> Matriz2D_Gnr<V>:: operator%(int modulin)
{
    Matriz2D_Gnr<V>res(this-> x, this->y);
    for(int i=0; i<this->x; i++)
    {
        for(int j=0; j<this->y; j++)
        {
            res.matriz[i][j] = obtVal(i,j, res.matriz);//%modulin;
        }
    }
    return res;

}

template <typename V>
void Matriz2D_Gnr<V>::transpuesta()
{
    Matriz2D_Gnr<V>medio(this->y,this->x);

    //Transposicion de la matriz
    for(int i=0; i<medio.x; i++)
    {
        for(int j=0; j<medio.y; j++)
        {
            medio.matriz[i][j] = obtVal(j,i);
        }
    }

    //Reintegracion de los valores ala matriz
    int temp = this->x;
    this->x = this->y;
    this->y = temp;
    this->matriz = medio;
}


#endif // MATRIZ2D_GNR_H_H
