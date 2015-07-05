/*
 * File:   Grafo.cpp
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 02:25 PM
 */

#include "Parse.h"
#include "Grafo.h"
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <limits> // std::numeric_limits
#include <vector>

#ifndef NULL
#define NULL 0
#endif // NULL

using namespace std;
using namespace line_parse;


#include "Grafo.h"
int vcf = 5;// esto es para el vcf
Grafo::Grafo(int cntVrt, int prbAdy) //, int prbAdy) {
{
    if (cntVrt >= 10) // && (0 <= prbAdy < 1)) {
    {
       // vcf = rand()% 5 +1 ;// esto es para el vdf
        this->cntVrt = cntVrt;
        arrVrt.resize(cntVrt);
        srand(time(NULL));
        default_random_engine generador(rand());
        normal_distribution<double> distribucion(prbAdy, 2.0);
        for (int i = 0; i < this->cntVrt; i++)
        {
            arrVrt[i].tmpChqVrs = 0;

            arrVrt[i].cntChqVrs = 0;
            int rnum = distribucion(generador);
            if (!xstAdy(i, rnum) && xstVrt(rnum))
            {
                arrVrt[i].lstAdy.push_back(rnum);
                arrVrt[rnum].lstAdy.push_back(i);
            }
        }
         azarizarTmpChqVrs(vcf);
    }
}

Grafo::Grafo(const Grafo& orig)
{
    if (orig.cntVrt > 0)
    {
        this->cntVrt = orig.cntVrt;
        arrVrt.resize(this->cntVrt);
        for (int i = 0; i < this->cntVrt; i++)
        {
            arrVrt[i].e = orig.obtEst(i);
            arrVrt[i].tmpChqVrs = orig.obtTmpChqVrs(i);
            arrVrt[i].cntChqVrs = orig.arrVrt[i].cntChqVrs;
            for (int j = 0; j < orig.arrVrt[i].lstAdy.size(); j++)
                arrVrt[i].lstAdy.push_back(orig.arrVrt[i].lstAdy[j]);
        }
    }
}

Grafo::Grafo(string nArch)
{
    ifstream file;
    file.open(nArch.c_str(), ios::in);
    if (file.is_open() && file.good())
       // cout << "ok"<< endl;
    {
       // vcf = rand()% 5 +1 ;// esto es para el vdf
        char line[256];
        memset(&line, 0, 256);//poner memoria en 0
        file.getline(line, 256); //primera linea
        string inits = line;
        cntVrt = totalDeVertices(inits);
        prmAdy = promedioAdy(inits);
        if (cntVrt < 0) return; // error
        arrVrt.resize(cntVrt);
        int count = 0;
        while (!file.eof() && count < cntVrt)
        {
            memset(&line, 0, 256); //volver a poner en 0 el char
            file.getline(line, 256);
            string linea = line;
            size_t cant = cantidad_elementos(linea);
            if (cant > 0)
            {
                arrVrt[count].e = S;
                arrVrt[count].tmpChqVrs = 0;
                arrVrt[count].cntChqVrs = 0;
                for (int j = 0; j < cant; j++)
                {
                    arrVrt[count].lstAdy.push_back(elemento(linea, j));
                }
                count++;
            }
            azarizarTmpChqVrs(vcf);
        }
        return;
        throw 1;
    }
}


//ya no es necesario

Grafo::~Grafo()
{
}

bool Grafo::xstVrt(int vrt) const
{
    return (vrt < cntVrt && vrt >= 0); // Devuelve true si vrt esta entre 0 y cntVrt
}

bool Grafo::xstAdy(int vrtO, int vrtD) const
{
    if (xstVrt(vrtO) && xstVrt(vrtD)) // Comprueba que el indice del vertice existe
    {
        int cantidad_adyacencias = arrVrt[vrtO].lstAdy.size();
        if (cantidad_adyacencias == 0) return false; // No hay adyacencias, por lo tanto la adyacencia no existe
        for (int i = 0; i < arrVrt[vrtO].lstAdy.size(); i++)
        {
            if (arrVrt[vrtO].lstAdy[i] == vrtD) return true;
        }
        return false;
    }
    return false; // No se encontro adyacencia o el vertice no existe
}

int Grafo::obtCntAdy(int vrt) const
{
    if (xstVrt(vrt))
    {
        return arrVrt[vrt].lstAdy.size();
    }
}

void Grafo::obtAdy(int vrt, vector<int>& vec) const
{
    if (xstVrt(vrt))
    {
        vec.clear();
        for (int i = 0; i < arrVrt[vrt].lstAdy.size(); i++)
        {
            vec.push_back(arrVrt[vrt].lstAdy[i]);
        }
    }
}


int Grafo::obtTotVrt() const
{
    return cntVrt;
}

int Grafo::obtTotAdy() const
{
    int cant = 0;
    for (int i = 0; i < cntVrt; i++)
    {
        cant += arrVrt[i].lstAdy.size();
    }
    return cant;
}

Grafo::E Grafo::obtEst(int vrt) const
{
    if (xstVrt(vrt) == true)
    {
        return arrVrt[vrt].e;
    }
}

bool Grafo::operator==(const Grafo& grf) const
{
    if (this->cntVrt != grf.cntVrt) return false;
    for (int i = 0; i < this->cntVrt; i++)
    {
        if (arrVrt[i].lstAdy.size() != grf.arrVrt[i].lstAdy.size()) return false;
        vector<int>ady, adygrf;
        obtAdy(i, ady);
        grf.obtAdy(i, adygrf);
        for (int j = 0; j < arrVrt[i].lstAdy.size(); j++)
        {
            if (ady[j] != adygrf[j])
            {
                return false;
            }
        }
    }
    return true;
}


int Grafo::obtTmpChqVrs(int vrt) const
{
    return arrVrt[vrt].tmpChqVrs;
}

int Grafo::obtCntChVrs(int vrt)const {

    return arrVrt[vrt].cntChqVrs;

}

double Grafo::promLongCmnsCrts() const
{
    int sum = 0, total = cntVrt * (cntVrt - 1) / 2;
    int **matriz = Floyd_Warshall();
    for (int i = 0; i < cntVrt; i++)
    {
        for (int j = i; j < cntVrt; j++)
        {
            if (xstAdy(i, j))
                sum += matriz[i][j];
        }
    }
    for (int i = 0; i < cntVrt; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
    return ((double) sum / (double) total);
}

int **Grafo::Floyd_Warshall() const
{
    int** path;
    path = new int*[cntVrt];
    for (int i = 0; i < cntVrt; i++)
    {
        path[i] = new int[cntVrt];
        path[i][i] = 0;
    }
    for (int i = 0; i < cntVrt; i++)
    {
        for (int j = 0; j < cntVrt; j++)
        {
            if (xstAdy(i, j))
            {
                path[i][j] = 1;
            }
            else
            {
                path[i][j] = std::numeric_limits<int>::max();
            }
        }
    }
    for (int k = 0; k < cntVrt; k++)
        for (int i = 0; i < cntVrt; i++)
            for (int j = 0; j < cntVrt; j++)
            {
                if (path[i][k] == std::numeric_limits<int>::max() || path[k][j] == std::numeric_limits<int>::max()) continue;
                int dt = path[i][k] + path[k][j];
                if (path[i][j] > dt)
                    path[i][j] = dt;
            }

    return path;
}

double Grafo::centralidadIntermedial(int vrt) const
{
}

double Grafo::coeficienteAgrupamiento(int vrt) const
{
    if (xstVrt(vrt))
    {
        double cant = (double) arrVrt[vrt].lstAdy.size(), triangles = 0.0;
        if (cant == 0 || cant == 1) return 0;
        double t_g = (cant * (cant - 1)) / 2;
        vector<int>ady;
        obtAdy(vrt, ady);
        for (int i = 0; i < cant; i++)
        {
            for (int j = i + 1; j < cant; j++)
            {
                if (xstAdy(ady[i], ady[j]))
                {
                    triangles++;
                }
            }
        }
        return (triangles / t_g);
    }
    return 0;
}

void Grafo::modEst(int vrt, E ne)
{
    if (xstVrt(vrt))
    {
        arrVrt[vrt].e = ne;
    }
}

void Grafo::modTmpChqVrs(int vrt, int nt)
{
    if(xstVrt(vrt)) arrVrt[vrt].tmpChqVrs = nt;
}

void Grafo::actCntChqVrs(int vrt)
{
    if(xstVrt(vrt)&& arrVrt[vrt].cntChqVrs == arrVrt[vrt].tmpChqVrs)
        arrVrt[vrt].cntChqVrs = 0;
    else
    {
        arrVrt[vrt].cntChqVrs++;
    }
}

void Grafo::infectar(int ios)
{
    if (ios < obtTotVrt())
    {
        vector<int>infectemos;
        int randy;
        bool esta = true;
        for (int i = 0; i < ios; i++)
        {
            while (esta)
            {
                randy = rand() % obtTotVrt();
                esta = false;
                for (int j = 0; j < infectemos.size(); j++)
                {
                    if(infectemos[j] == randy) esta = true;
                }
            }
            infectemos.push_back(randy);
            esta = true;
        }
        for (int i=0; i<infectemos.size(); i++)
        {
            arrVrt[infectemos[i]].e = I;
        }
    }
}


void Grafo::azarizarTmpChqVrs(int vcf)
{
    int randy;
    for (int i = 0; i < obtTotVrt(); i++)
    {
        randy = rand() % vcf + 1;
        arrVrt[i].tmpChqVrs = randy;
    }
}

void Grafo::modEstados(vector<NdoVrt>& stdAct)
{
}
