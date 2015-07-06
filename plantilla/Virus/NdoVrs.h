#ifndef NDOVRS_H
#define NDOVRS_H

#include <memory>
#include <vector>
#include <string>

#include "../GrafoGnr.h"
#include "../VerticeGnr.h"

bool prob(double probability);

using namespace std;

class NdoVrs : public VerticeGnr
{

public:

    enum E  // representa el tipo de estados de la red de infección
    {
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };


    NdoVrs();
    NdoVrs(const NdoVrs& vr);
   // NdoVrs(string str);
    virtual ~NdoVrs();

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el estado del vértice con índice vrt.
    E obtEst() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del temporizador de chequeo de antivirus del vértice con índice vrt.
    int obtTmpChqVrs() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del contador de chequeo de antivirus del vértice con índice vrt.
    int obtCntChVrs() const;

    Vector3 obtColor();


    /* MÉTODOS MODIFICADORES */

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el estado del vértice cuyo índice es vrt a ne.
    void modEst(E ne);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el valor del temporizador de chequeo de virus del vértice vrt por el valor nt.
    void modTmpChqVrs(int nt);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: actualiza el valor del contador de chequeo de virus para la siguiente iteración.
    void actCntChqVrs();

    // MOD: *this
    // EFE: asigna el valor del temporizador para cada vértice con un número al azar entre 1 y maxTmp.
    //      vcf o virus-check-frecuency: frecuencia máxima de chequeo antivirus.
    void azarizarTmpChqVrs();

    //MOD:*this
    //EFE: calcula el estado de un vertice a partir de sus vecinos
    void calcEst(vector<VerticeGnr*>& ady);

    //bool operator==(const VerticeGnr& vr);

   // void operator=(const VerticeGnr& vr) const;

protected:

private:
        E e; // representa el estado del vértice
        int tmpChqVrs; // representa el temporizador de chequeo de virus
        int cntChqVrs; // representa el contador de chequeo de virus: va de 0 a tmpChqVrs
        // No va a ser necesario un destructor porque ahora todo se manejará automáticamente
};

#endif // NDOVRS_H
