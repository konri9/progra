#include "NdoAve.h"
#include "GrafoGnr.h"
#include <iostream>
#include <chrono>
#include <memory>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <limits> // std::numeric_limits

using namespace std;

NdoAve::NdoAve(){
    e = R;
    azarizarEstres();
}

NdoAve::NdoAve(const NdoAve& ave){
	e = ave.e;
	niv_strs = ave.niv_strs;

}

NdoAve::~NdoAve()
{
    
}

NdoAve::E NdoAve::obtEst() const
{
    return e;
}

Vector3 NdoAve::obtColor()
{
    if (!esAve()) return Vector3(0.0, 0.0, 0.0);
    if (niv_strs >= MAX_ESTRES-0.2) return Vector3(0.0, 0.0, 1.0);
    return Vector3(niv_strs/MAX_ESTRES, 0.0, 0.0);
}


double NdoAve::obtEstres() const
{
    return niv_strs;
}

void NdoAve::ponerAve()
{
    es_ave = true;
}

bool NdoAve::esAve()
{
    return es_ave;
}

void NdoAve::modEst(E ne)
{
        e = ne;
}

void NdoAve::modEstres(double n_estres)
{
    niv_strs = n_estres;
}

void NdoAve::azarizarEstres()
{
    double randy =((double)rand() / (double)RAND_MAX)*MAX_ESTRES;
        niv_strs = randy;
}

// calcula el nuevo estado con la relacion
// La relacion es osl = oslanterior  (1+NR) + promedio*NR del nivel de estres de los vecinos
double NdoAve::calcEstres(double NR, vector<double>& niveles_str)//const;
{
    double sum = 0, res = 0;
    for(int i=0; i<niveles_str.size(); i++)
    {
        sum+= niveles_str[i];
    }
    double promedio = (double)(sum / (double)niveles_str.size());
    res = niv_strs*(1+NR)+promedio*NR;
    return res;
 }


