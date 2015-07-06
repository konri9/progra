/* 
 * File:   Monomio.cpp  
 * Author: Konrad
 * 
 * Created on March 16, 2015, 11:32 AM
 */

#include "Monomio.h"
#include <iostream>
#include<sstream>
#include<string>
using namespace std;

Monomio::Monomio() : c(0), expX(0), expY(0) { //inicializan atributos en linea

}

Monomio::Monomio(const Monomio& orig) : c(orig.c), expX(orig.expX), expY(orig.expY) {
}

Monomio::Monomio(string e) { //agarra un string y lo pasa a un monomio
    std::string po = "X";
    std::size_t r = e.find(po); //aca lo rastrea
    std::string u = e.substr(0, r); //aca almacena el coeficiente
    const char* ca = u.c_str();
    this->c = atof(ca);

    po = "(";
    r = e.find(po); // size es un int
    u = e.substr(r+1, 1); //aca almacena el coeficiente
    ca = u.c_str(); // aca lo convierto de string
    this->expX = atof(ca);

    po = "Y";
    r = e.find(po); // size es un int
    u = e.substr(r+2, 1); //aca almacena el coeficiente
    ca = u.c_str();
    this->expY = atof(ca);

}

Monomio::~Monomio() { //constructor
}

//Estos son los getters
double Monomio::obtC() {
    return c;
}

int Monomio::obtExpX() {
    return expX;
}

int Monomio::obtExpY() {
    return expY;
}

//Estos son los setters
void Monomio::asgC(double nC) {
    c = nC;
}

//Aqui asigna los exponentes
void Monomio::asgExpX(int nX) {
    if (nX >= 0) {
        expX = nX;
    } else {
        expX = 0;
    }
}

void Monomio::asgExpY(int nY) {
    if (nY >= 0) {
        expY = nY;
    } else {
        expY = 0;
    }
}

Monomio Monomio::operator+(const Monomio& op)  throw (ExcMonomioInvalido&) {
    Monomio mr; 
   if(op.c != 0 && this->c !=0 && (this-> expX != op.expX || this-> expY != op.expY)) throw ExcMonomioInvalido(1); //monomios no son semejantes
     else if (this->c == 0){
        mr.c = op.c;
        mr.expX = op.expX;
        mr.expY = op.expY;
    }else if(this->c == -op.c){// encuentra el inverso aditivo
           mr.c = 0;
           mr.expX = 0;
           mr.expY =  0;    
       }  else{
        mr.c = this->c +op.c;
        mr.expX = this->expX;
        mr.expY = this->expY;
   }
       return mr;   
       }
    

Monomio Monomio::operator-(const Monomio& op) throw (ExcMonomioInvalido&) {
    Monomio mr;
   if(op.c != 0 && this->c !=0 && (this-> expX != op.expX || this-> expY != op.expY)) throw ExcMonomioInvalido(1); //monomios no son semejantes
    else if(op.c == 0){
            mr.c = this->c;
        mr.expX = this->expX;
        mr.expY = this->expY;
    } else if (this->c == 0){
        mr.c = -op.c;
        mr.expX = op.expX;
        mr.expY = op.expY;
    }else if(this->c == op.c){// encuentra el inverso aditivo
           mr.c = 0;
           mr.expX = 0;
           mr.expY =  0;    
       }  else{
        mr.c = this->c -op.c;
        mr.expX = this->expX;
        mr.expY = this->expY;
    }   return mr;   
}

Monomio Monomio::operator*(const Monomio& op) throw (ExcMonomioInvalido&) {
    Monomio mn;
    if(this->c == 0 || op.c ==0){
        mn.c = 0;
        mn.expX = 0;
        mn.expY = 0;
    }else {
    mn.c = this->c * op.c;
    mn.expX = this->expX + op.expX;
    mn.expY = this->expY + op.expY;
    }
    return mn;
    
}

Monomio Monomio::operator/(const Monomio& op) throw (ExcMonomioInvalido&) {
    Monomio mn;
    if (this->c==0 || this->expX == 0 || this->expY ==0){
        mn.c = 0;
        mn.expX = 0;
        mn.expY = 0;
    }else if (op.c == 0 || op.expX == 0 || op.expY == 0) {
        throw ExcMonomioInvalido(0); //0 = division por monomio cero
    } else if (op.expX > this->expX || op.expY > this->expY) {
        throw ExcMonomioInvalido(2); //2= exponente invalido en el divisor
    }else if(this->c == 0 && this->expX==0 && expY==0){
        mn.c = 0; //
        mn.expX = 0;
        mn.expY = 0;
    } else {
           mn.c = this->c / op.c;
           mn.expX = this->expX - op.expX;
           mn.expY = this->expY - op.expY;
    }
        return mn;
}

string Monomio::aHil() { // agarra un monomio y lo pasa a string
    stringstream in; // esto es un stream de strings
    string res;
    string cofi;
    string decimales;
    stringstream coef;
    coef <<this->c;
    res = coef.str();//0.4738764783
    string punto = "."; //"0.47169X(1)Y(0)"
    size_t r = res.find(punto);
    cofi = res.substr(0, r+1);
    decimales = res.substr(r+1, 5);// aca corto el numero
    res = cofi + decimales;
    in << res << "X(" << this->expX << ")Y(" << this-> expY << ")";//("5.3X(2)Y(3)")    
    res = in.str();
    return res;
    
}