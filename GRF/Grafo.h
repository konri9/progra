/*
 * File:   Grafo.h
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 02:25 PM
 */

#ifndef GRAFO_H
#define	GRAFO_H

#include <memory>
#include <vector>
#include <string>
using namespace std;

class Grafo {
    // Representa la red de computadores sobre la cual se diseminará el virus.

public:
    // Simulador y Visualizador ya no son amigas.

    /* TIPO PÚBLICO DE ESTADOS DE VÉRTICES */
    enum E{ // representa el tipo de estados de la red de infección
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };

    /* CONSTRUCTORES */
    // REQ: ( cntVrt >= 10 ) && ( 0 <= prbAdy < 1  )
    // Construye una red al azar no vacía. La probabilidad de que exista una adyacencia (i,j) es prbAdy.
    Grafo(int cntVrt, int prbAdy);

    // Construye una copia idéntica a orig.
    Grafo(const Grafo& orig);

    // Construye una red con base en los datos en el archivo de nombre nArch.
    // El archivo debe ser *.txt con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad de vértices.
    // Luego en cada línea aparecerá primero el estado de un vértice y las posiciones
    // de los adyacentes, todo separado por comas.
    Grafo(string nArch);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~Grafo();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si existe un vértice con índice vrt.
    bool xstVrt(int vrt) const;

    // REQ: existan en *this vértices con índices vrtO y vrtD.
    // EFE: retorna true si existe un arco entre los vértices con índice vrtO y vrtD.
    bool xstAdy(int vrtO, int vrtD) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna la cantidad de adyacencias del vértice vrt.
    int obtCntAdy(int vrt) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna un vector de enteros con las posiciones de los vértices
    //      adyacentes al vértice indicado por vrt.
    void obtAdy(int vrt, vector<int>& vec)const;

    // EFE: retorna el total de vértices en *this.
    int obtTotVrt() const;

    // EFE: retorna el total de adyacencias en *this.
    int obtTotAdy() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el estado del vértice con índice vrt.
    E obtEst(int vrt) const;


    // EFE: retorna true si grf es idéntico a *this y false en caso contrario.
    //      Compara vértice a vértice según su índice.
    bool operator==(const Grafo& grf) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del temporizador de chequeo de antivirus del vértice con índice vrt.
    int obtTmpChqVrs(int vrt) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del contador de chequeo de antivirus del vértice con índice vrt.
    int obtCntChVrs(int vrt) const;

    /* MÉTODOS OBSERVADORES ESPECIALES */

    // EFE: retorna el promedio de las longitudes de los caminos más cortos
    //      entre cada pareja de vértices de *this.
    double promLongCmnsCrts() const;

    // REQ: vrt sea un índice de vértice válido.
    // EFE: retorna la "betweeness centrality" o centralidad intermedial del vértice con índice vrt.
    //      La definición aparece en: http://en.wikipedia.org/wiki/Betweenness_centrality
    //      Para cada par de vértices que no incluyan al indicado por vrt se calcula
    //      la proporción de los caminos más cortos que pasan por el vértice indicado
    //      por vrt.
    // NOTA: sigue pendiente para el cuarto laboratorio guiado porque requiere una nueva clase.
    double centralidadIntermedial(int vrt) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el "local clustering coefficient" o coeficiente local de agrupamiento
    //      para el vértice indicado por vrt.
    //      La definición aparece en: http://en.wikipedia.org/wiki/Clustering_coefficient
    //      Se calcula como el cociente entre la cantidad efectiva de arcos entre los
    //      vecinos del vértice indicado por vrt dividida por la cantidad total de posibles
    //      arcos entre todos los vecinos del vértice indicado por vrt.
    double coeficienteAgrupamiento(int vrt) const;

    /* MÉTODOS MODIFICADORES */

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el estado del vértice cuyo índice es vrt a ne.
    void modEst(int vrt, E ne);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el valor del temporizador de chequeo de virus del vértice vrt por el valor nt.
    void modTmpChqVrs(int vrt, int nt);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: actualiza el valor del contador de chequeo de virus para la siguiente iteración.
    void actCntChqVrs(int vrt);

    // REQ: ios << this->obtTotVrt().
    // MOD: *this.
    // EFE: cambia el estado a I (infectado) a ios vértices escogidos al azar.
    //      ios o initial-outbreak-size: cantidad inicial de nodos infectados.
    void infectar(int ios);

    // MOD: *this
    // EFE: asigna el valor del temporizador para cada vértice con un número al azar entre 1 y maxTmp.
    //      vcf o virus-check-frecuency: frecuencia máxima de chequeo antivirus.
    void azarizarTmpChqVrs(int vcf);

    int **Floyd_Warshall() const;

private:
    struct NdoVrt {
        E e; // representa el estado del vértice
        int tmpChqVrs; // representa el temporizador de chequeo de virus
        int cntChqVrs; // representa el contador de chequeo de virus: va de 0 a tmpChqVrs
        // Escoja entre <vector>, <list> y <forward_list> para representar la lista de adyacencias del vértice.
        vector <int> lstAdy;
        NdoVrt(): e(S), tmpChqVrs(1){};
        // No va a ser necesario un destructor porque ahora todo se manejará automáticamente
    };

    int cntVrt; // representa la cantidad total de vértices
    double prmAdy;
    // Escoja entre <vector>, <map> y <unordered_map> en lugar del arreglo de nodos de vértices.

    vector<NdoVrt>arrVrt;

    void modEstados(vector<NdoVrt>& stdAct);
};

#endif	/* GRAFO_H */

