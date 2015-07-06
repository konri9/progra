/* 
 * File:   pba_monomio.cpp
 * Author: Konrad
 *
 * Created on Mar 19, 2015, 9:37:15 AM
 */

#include <stdlib.h>
#include <iostream>
#include "Monomio.h"
#include "ExcMonomioInvalido.h"

/*
 * Simple C++ Test Suite
 */

void testMonomio() { //invoca al constructor monomio
    Monomio monomio;
    if ((monomio.obtC() != 0) || (monomio.obtExpX() != 0) || (monomio.obtExpY() != 0)) { //si el monomio falla entonces saca por consola que falla 
        std::cout << "%TEST_FAILED% (pba_monomios)FALLO EL CONSTRUCTOR ESTANDAR" << std::endl;
    }
}

void testMonomio2() {
    const Monomio orig;
    Monomio monomio(orig);
    if ((monomio.obtC() != 0) || (monomio.obtExpX() != 0) || (monomio.obtExpY() != 0)) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONSTRUCTOR DE COPIAS 1" << std::endl;
    }
    //Segunda prueba
    Monomio m;
    m.asgC(5.5);
    m.asgExpX(2);
    m.asgExpY(1);

    Monomio m1(m); //aca
    if ((m1.obtC() != 5.5) || (m.obtExpX() != 2) || (m.obtExpY() != 1)) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONSTRUCTOR DE COPIAS 2" << std::endl;
    }

}

void testMonomio3() {
    string p0 = "2.3X(2)Y(2)";
    Monomio monomio(p0);
    if (monomio.obtC() != 2.3 || monomio.obtExpX() != 2 || monomio.obtExpY() != 2) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONSTRUCTOR A PARTIR DE HILERA #1" << std::endl;
    }
    
    p0 = "-2.3X(2)Y(2)";
    monomio = Monomio(p0);
    if (monomio.obtC() != -2.3 || monomio.obtExpX() != 2 || monomio.obtExpY() != 2) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONSTRUCTOR A PARTIR DE HILERA #2" << std::endl;
    }
    p0 = "0X(0)Y(0)";
    monomio = Monomio(p0);
    if (monomio.obtC() != 0 || monomio.obtExpX() != 0 || monomio.obtExpY() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONSTRUCTOR A PARTIR DE HILERA #3" << std::endl;
    }

}

void testaHil() {
    Monomio m1("2.3X(2)Y(2)");
    string hr = m1.aHil();
    if (hr != "2.3X(2)Y(2)") {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONVERTIDOR DE HILERA #1" << std::endl;
    }

    Monomio m2("-2.3X(2)Y(2)");
    hr = m2.aHil();
    if (hr != "-2.3X(2)Y(2)") {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONVERTIDOR DE HILERA #2" << std::endl;
    }

    Monomio m3;
    hr = m3.aHil();
    if (hr != "0X(0)Y(0)") {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL CONVERTIDOR DE HILERA #3" << std::endl;
    }
}

void testAsgC() {
    double nc = 5.3;
    Monomio monomio;
    monomio.asgC(nc);
    if (monomio.obtC() != 5.3) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL ASIGNADOR DEL COEFICIENTE #1" << std::endl;
    }

    nc = 0;
    monomio.asgC(nc);
    if (monomio.obtC() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL ASIGNADOR DEL COEFICIENTE #2" << std::endl;
    }
}

void testAsgExpX() {
    int nX = 3; //dividir en valores validos e invalidos
    Monomio monomio;
    monomio.asgExpX(nX);
    if (monomio.obtExpX() != 3) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL ASIGNADOR DEL EXPONENTE X #1" << std::endl;
    }

    nX = -3;
    monomio.asgExpX(nX);
    if (monomio.obtExpX() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL ASIGNADOR DEL EXPONENTE X #2" << std::endl;
    }
}

void testAsgExpY() {
    int nY = 3;
    Monomio monomio;
    monomio.asgExpY(nY);
    if (monomio.obtExpY() != 3) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL ASIGNADOR DEL EXPONENTE Y #1" << std::endl;
    }

    nY = -3;
    monomio.asgExpY(nY);
    if (monomio.obtExpY() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EL ASIGNADOR DEL EXPONENTE Y #2" << std::endl;
    }
}

void testOperatorSuma() { // Considerar 3 situaciones: monomio semejantes, 
    Monomio m0; // monomio CERO
    Monomio m1("5.3X(2)Y(3)");
    Monomio m4("-5.3X(2)Y(3)"); // opuesto aditivo de m1
    Monomio m5("2.2X(3)Y(3)"); //monomio no semejante
    Monomio mr = m0 + m1; // deberia dar m1
    if ((mr.obtC() != 5.3) || mr.obtExpX() != 2 || mr.obtExpY() != 3) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR SUMA #1" << std::endl;
    }
   
    mr = m1 + m4;  
    if ((mr.obtC() != 0) || mr.obtExpX() != 0 || mr.obtExpY() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR SUMA #2" << std::endl;
    }

    try {
        m1 + m5;
    } catch (ExcMonomioInvalido& e) {
        cout << string("%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR SUMA #3") + string(e.what()) << std::endl;
    }
}

void testOperatorResta() {
    Monomio m0; // monomio CERO
    Monomio m1("5.3X(2)Y(3)");
    Monomio m4("-5.3X(2)Y(3)"); // opuesto aditivo de m1
    Monomio m5("2.2X(3)Y(3)"); //monomio no semejante
    Monomio mr = m1 - m0; // deberia dar m1
    if ((mr.obtC() != 5.3) || mr.obtExpX() != 2 || mr.obtExpY() != 3) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR RESTA #1" << std::endl;
    }

    mr = m0 - m1; //busca el opuesto aditivo
    if ((mr.obtC() != -5.3) || mr.obtExpX() != 2 || mr.obtExpY() != 3) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR RESTA #2" << std::endl;
    }

    mr = m1 - m1; // aca vamos a restar el monomio consigo mismo

    if ((mr.obtC() != 0) || mr.obtExpX() != 0 || mr.obtExpY() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR RESTA #3" << std::endl;
    }

    try {
        m1 - m5;
    } catch (ExcMonomioInvalido& e) {
        cout << string("%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR RESTA #4") + string(e.what())<< std::endl;
    }
}

void testOperatorMultiplicacion() {
    Monomio m0; // monomio CERO
    Monomio m1("5.3X(2)Y(3)");
    Monomio m4("-5.3X(2)Y(3)"); // opuesto aditivo de m1
    Monomio mr = m1 * m0; // deberia dar m0

    if ((mr.obtC() != 0) || mr.obtExpX() != 0 || mr.obtExpY() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR MULTIPLICACION #1" << std::endl;
    }
    mr = m1 * m4;
    if ((mr.obtC() != -28.09) || mr.obtExpX() != 4 || mr.obtExpY() != 6) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR MULTIPLICACION #2" << std::endl;
    }


}

void testOperatorDivision() {
    Monomio m0; // monomio CERO
    Monomio m1("5.3X(2)Y(3)");
    Monomio m3("2.5X(3) Y(3)");
    Monomio m4 ("3.2X(5)Y(3)");
    Monomio mr; 
   
    try{
    mr = m0 / m1;
    if ((mr.obtC() != 0) || mr.obtExpX() != 0 || mr.obtExpY() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR DIVISION #1" << std::endl;
    }
    } catch (ExcMonomioInvalido& e){
        cout << string("%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR DIVISION #1") + e.what() << std::endl;   
    }
    
    mr = m3 / m1;
    string hr = mr.aHil();
    if ((hr != "0.47169X(1)Y(0)") || mr.obtExpX() != 1 || mr.obtExpY() != 0) {
        std::cout << "%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR DIVISION #2" << std::endl;
    }

    
    try {
      m1 /m4;   
    } catch (ExcMonomioInvalido & e){
        cout << string("%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR DIVISION #3") + string(e.what()) << std::endl;
    }
    try{
        m1/m0;
    } catch (ExcMonomioInvalido & e){
        cout << string("%TEST_FAILED% (pba_monomios) FALLO EN EL OPERADOR DIVISION #4") + string(e.what()) << std::endl;
    }
    
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% pba_monomio" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testMonomio (pba_monomio)" << std::endl;
    testMonomio();
    std::cout << "%TEST_FINISHED% time=0 testMonomio (pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED% testMonomio2 (pba_monomio)" << std::endl;
    testMonomio2();
    std::cout << "%TEST_FINISHED% time=0 testMonomio2 (pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED% testMonomio3 (pba_monomio)" << std::endl;
    testMonomio3();
    std::cout << "%TEST_FINISHED% time=0 testMonomio3 (pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED% testaHil (pba_monomio)" << std::endl;
    testaHil();
    std::cout << "%TEST_FINISHED% time=0 testAhil (pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED% testAsgC (pba_monomio)" << std::endl;
    testAsgC();
    std::cout << "%TEST_FINISHED% time=0 testAsgC (pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED% testAsgExpX (pba_monomio)" << std::endl;
    testAsgExpX();
    std::cout << "%TEST_FINISHED% time=0 testAsgExpX (pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED% testAsgExpY (pba_monomio)" << std::endl;
    testAsgExpY();
    std::cout << "%TEST_FINISHED% time=0 testAsgExpY (pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED%  testOperatorSuma(pba_monomio)" << std::endl;
    testOperatorSuma();
    std::cout << "%TEST_FINISHED% time=0  testOperatorSuma(pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED%  testOperatorResta(pba_monomio)" << std::endl;
    testOperatorResta();
    std::cout << "%TEST_FINISHED% time=0  testOperatorResta(pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED%  testOperatorMultiplicacion(pba_monomio)" << std::endl;
    testOperatorMultiplicacion();
    std::cout << "%TEST_FINISHED% time=0  testOperatorMultiplicacion(pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED%  testOperatorDivision(pba_monomio)" << std::endl;
    testOperatorDivision();
    std::cout << "%TEST_FINISHED% time=0  testOperatorDivision(pba_monomio)" << std::endl;

    std::cout << "%TEST_STARTED%  testOperatorSuma(pba_monomio)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

