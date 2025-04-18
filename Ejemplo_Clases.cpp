#include <iostream>
using namespace std;

template <typename T>
class Persona{
    private:
    T nombre;
    unsigned int edad;
    unsigned int id;

    public:
    Persona(T n, unsigned int e, unsigned int i){
        nombre = n;
        edad = e;
        id = i;
    }

    public:

    void print(){
        cout << "Nombre: " << nombre << endl << "Edad: " << edad << endl << "Identificacion: " << id << endl;
    }

};

int main (){
    Persona P1("Martin Barrero Lopez", 17, 1055764765);
    P1.print();

    return 0;
}