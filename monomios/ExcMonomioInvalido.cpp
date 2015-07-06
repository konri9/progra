/* 
 * File:   ExcMonomioInvalido.cpp
 * Author: Konrad
 * 
 * Created on March 25, 2015, 12:11 AM
 */

#include "ExcMonomioInvalido.h"

ExcMonomioInvalido::ExcMonomioInvalido():invalid_argument("Monomio invalido:"), tipo(0) {
}

ExcMonomioInvalido::ExcMonomioInvalido(int te):invalid_argument("Monomio invalido:"), tipo(te) {
}


const char* ExcMonomioInvalido:: what() const throw(){
    string err;
    if (tipo == 0){
       err = string(invalid_argument::what())+ string("se intenta division por monomio cero");
    } else if (tipo == 1) {
        err = string(invalid_argument::what())+ string("se intenta operacion con monomios no semejantes");
    } else { //tipo 2
       err = string(invalid_argument::what())+ string("se intenta una division con exponentes mayores en el dividendo"); 
    }
    return err.c_str();
}

