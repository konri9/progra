/* 
 * File:   Monomio.h
 * Author: Konrad
 *
 * Created on March 16, 2015, 11:32 AM
 */

#ifndef MONOMIO_H
#define	MONOMIO_H

#include<iostream> // incluye la biblioteca iostream para usar los strings
#include<stdlib.h> // incluye el atof
using namespace std; //incluye el espacio de nombres standard

#include "ExcMonomioInvalido.h"
class Monomio {
public:
    // EFE: construye una nueva instancia del monomio igual al monomio cero
    Monomio(); // constructor basico o estandar (no tiene parametros)

    //EFE: construye una copia identica (clona) al objeto orig
    Monomio(const Monomio& orig); // constructor de copias

    //EFE: Costruye una instancia basada en la hilera prevista
    Monomio(string);
    virtual ~Monomio(); // el virtual no es oblgatorio. Destructor


    //Aca vienen los metodos principales

    //Estos son los getters
    double obtC();
    int obtExpX();
    int obtExpY();

    /*Estos son los setters*/
    void asgC(double nC);

    //EFE: asigna nX como exponente de X a *this si nX >= 0, de lo contrario asignara 0
    //EFE: si nX <0 asigna cero al exponente de la x
    void asgExpX(int nX);

    //EFE: asigna nY como exponente de Y a *this si nY >= 0, de lo contrario asignara 0
    void asgExpY(int nY);

    //REQ: *this como op deben estar bien construidos. (*this es para referenciar el objeto que esta recibiendo el msj)
    //MOD: n/a
    //EFE: retorna un nuevo monomio con la suma de *this y op
    //si *this y op son opuestos aditivos ---> monomio cero
    //EXC: cuando los monomios no sean semejantes
    Monomio operator+(const Monomio& op) throw (ExcMonomioInvalido&); //recibe un monomio por referencia

    //REQ: *this como op deben estar bien construidos. (*this es para referenciar el objeto que esta recibiendo el msj)
    //MOD: n/a
    //EFE: retorna un nuevo monomio con la resta de this y op
    //EXC: cuando los monomios no sean semejantes.
    Monomio operator-(const Monomio& op)  throw (ExcMonomioInvalido&); // sobrecargar el op


    //REQ: *this como op deben estar bien construidos. (*this es para referenciar el objeto que esta recibiendo el msj)
    //MOD: n/a
    //EFE: retorna un nuevo monomio con la multiplicacion de this y op.
    Monomio operator*(const Monomio& op)  throw (ExcMonomioInvalido&); // no queremos que a los orig se cambien

    //REQ: *this como op deben estar bien construidos. (*this es para referenciar el objeto que esta recibiendo el msj)
    //MOD: n/a
    //EFE: retorna un nuevo monomio con el cociente de this y op
    //EXC-1: cuando op es el monomio CERO.
    //EXC-2: cuando op tiene algun exponente mayor que el correspondiente en *this
    Monomio operator/(const Monomio& op)  throw (ExcMonomioInvalido&); //

    //REQ: *this este bien construido
    //MOD: n/a
    //EFE: retorna una hilera 
    
    string aHil(); //transforma hilera en monomio


private:
    double c; // representa el coeficiente del monomio
    int expX; // representa el exponente de la x
    int expY; // representa el exponente de la y
};

#endif	/* MONOMIO_H */



