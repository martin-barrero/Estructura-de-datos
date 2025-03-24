#include <iostream>
using namespace std;

int main (){
    int *p = new int;
    cout << "Por favor ingrese un número entero: " << endl;
    cin >> *p;
    cout << endl << "El número ingresado fue: " << *p << endl;
    delete p;

    return 0;
}

/*
int main (){
    int numero = 10;
    int *p_numero = &numero;

    cout << "Número variable: " << numero << endl;
    cout << "Número puntero: " << *p_numero << endl;
    cout << "Dirección variable: " << &numero << endl;
    cout << "Dirección puntero: " << p_numero << endl;

    *p_numero = 20;
    cout << "Número modificado por puntero (Variable): " << numero << endl;
    cout << "Número modificado por puntero (Puntero): " << *p_numero << endl;
    cout << "Dirección (Debe ser igual): " << p_numero <<  " y " << &numero <<  endl;

    return 0;
}
*/