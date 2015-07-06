/* 
 * File:   main.cpp
 * Author: Konrad
 *
 * Created on March 12, 2015, 9:26 AM
 */

#include <iostream>
using namespace std;

#include "Monomio.h" // aqui ligo las dos clases
#include"ExcMonomioInvalido.h"
/*
 * 
 */
int main(int argc, char** argv) {
    Monomio m0;//Monomio 0
    Monomio m1 ("5.3X(2)Y(3)");
    Monomio m2 ("3.4X(2)Y(3)");
    Monomio m3 ("2.5X(3)Y(3)");
    Monomio m4 ("-5.3X(2)Y(3)"); //opuesto aditivo de m1
    Monomio m5("2.2X(3)Y(3)"); //monomio no semejante
    
    try{
        m4+m5;
    }catch(ExcMonomioInvalido& e){
        cout << e.what() <<endl;
    }
    return 0;
}

 