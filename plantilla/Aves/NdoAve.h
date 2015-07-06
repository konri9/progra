#ifndef NDOAVE_H
#define NDOAVE_H

#include <memory>
#include <vector>
#include <string>

#define MAX_ESTRES 1.0f

#include "../GrafoGnr.h"
#include "../VerticeGnr.h"

bool prob(double probability);

using namespace std;

class NdoAve : public VerticeGnr
{

public:

// Nivel de estres de las aves!
    enum E  // representa el nivel de estres de las aves
    {
        M, // representa un vertice sin ave
        R, // representa un vertice de ave relajada
		S, // representa un vértice de ave con estresada
        P, // representa un vértice de ave ya terminada
     //   SSS // representa un vÉrtice de ave estresada
    };


    NdoAve();
	NdoAve(const NdoAve& vr);
	//ctor de copias

    virtual ~NdoAve();

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el estado del vértice con índice vrt.
    E obtEst() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el nivel de estres del ave con índice vrt.
    double obtEstres() const;
    
    void ponerAve();
    
    bool esAve();

	Vector3 obtColor();


    /* MÉTODOS MODIFICADORES */

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el estado del vértice cuyo índice es vrt a ne.
    void modEst(E ne);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el valor del nivel de estres por el valor n_estres.
    void modEstres(double n_estres);

    // MOD: *this
    // EFE: asigna el valor del temporizador para cada vértice con un número al azar entre 1 y maxTmp.
    //      vcf o virus-check-frecuency: frecuencia máxima de chequeo antivirus.
    void azarizarEstres();

    //EFE: calcula el estado de un vertice a partir de sus vecinos
    // Retorna el nuevo nivel de estres del ave con base en la relacion
    // La relacion es os = NR*oslanterior  (1+NR) * promedio del nivel de estres de los vecinos
    double calcEstres(double NR, vector<double>& niveles_str); //const;

protected:
    
private:
        E e; // representa el estado del vértice
        double niv_strs; // representa el temporizador de chequeo de virus
        bool es_ave = false; // representa si hay un ave o no en este vertice
};

#endif // NDOAVE_H
