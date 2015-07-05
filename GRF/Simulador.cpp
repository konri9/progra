/*
 * File:   Simulador.cpp
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 06:46 PM
 */

#include <random>
#include <ctime>
#include <iostream>
#include "Simulador.h"

bool prob(double probability) // probability < 1
{
    double result = (double)rand() / (double)RAND_MAX;
    if(result < probability)
        return true;
    return false;
}

Simulador::Simulador(Grafo *g):grafo(g) {
}

Simulador::~Simulador() {
}

//ios: cantidad de vertices infectados
//vsc: probabilidad de infeccion
//vcf: checkeo de virus----> Ya no se ocupa entonces
//rc: probabilidad de recuperacion
//grc: probabilidad de obtener resistencia
void Simulador::simular(int cntItr, int ios, double vsc, double rc, double grc) {
    if (grafo == NULL) return;
    srand(time(NULL));
    int temp, cont = 0;
    Grafo grafo2(*grafo);

    for (int i = 0; i < ios; i++) // asigna aleatoreamente ios cantidad de vertices infectados al azar
    {
        int id = rand() % grafo->obtTotVrt();
        if (grafo->xstVrt(id))
        {
            if (grafo->obtTotVrt() < ios)
            {
                for (int i = 0; i < grafo->obtTotVrt(); i++)
                {
                    grafo->modEst(i, Grafo::I);
                }
            }
            else
            {
                while (grafo->obtEst(id) == Grafo::I) // si el que encontro ya esta infectado, pide e infecta otro...
                {
                    id = rand() % grafo->obtTotVrt();
                }
                grafo->modEst(id, Grafo::I);
            }
        }
    }


 //Aca son las iteraciones
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            temp = grafo->obtTmpChqVrs(j); //obtiene el temporizador de checkeo de virus del vertice

            if (grafo2.obtEst(j) == Grafo::I)// si el vertice esta infectado
            {
             // se mofica
                vector<int>ady;
                grafo->obtAdy(j,ady);
                for (int k = 0; k < ady.size(); k++)
                {
                    if (grafo2.obtEst(ady[k]) != Grafo::R && prob(vsc))// y el adyacente no es resistente
                    {
                        grafo->modEst(ady[k], Grafo::I);//infecta los demas vertices
                    }
                }
                cont = grafo->obtCntChVrs(j);
                if (cont == temp)
                {
                    if (prob(rc))
                    {
                        grafo->modEst(j, Grafo::S);
                        if (prob(grc))
                        {
                            grafo->modEst(j, Grafo::R);
                        }
                    }
                }
            }
            grafo->actCntChqVrs(j);//Actualiza el contador
        }
       /* for (int n = 0; n < grafo->obtTotVrt(); n++)
        {
            grafo2.modEst(n, grafo->obtEst(n));
        }*/
    }
}

void Simulador::asignarGrafo(Grafo* g)
{
    grafo = g;
}
