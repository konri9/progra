/* 
 * File:   ExcMonomioInvalido.h
 * Author: Konrad
 *
 * Created on March 25, 2015, 12:11 AM
 */

#ifndef EXCMONOMIOINVALIDO_H
#define	EXCMONOMIOINVALIDO_H

#include<stdexcept>
#include<iostream>
using namespace std;

class ExcMonomioInvalido: public invalid_argument {
public:
    ExcMonomioInvalido();
    ExcMonomioInvalido(int);
   const char* what() const throw();
private:
    int tipo;// 0= monomio 0, 1 = no semej, 2 = exp invalido en divisor
};

#endif	/* EXCMONOMIOINVALIDO_H */

