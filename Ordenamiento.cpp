#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int dividir(vector<int>& vectorInicial, int left, int right) {
    int pivote = vectorInicial.at(right); // Pivote al final
    int indice = left; // Índice para colocar elementos menores que el pivote (los recorre todos de derecha a izquerda ps por loq el pivote esta a toda la derecha)

    for (int k = left; k < right; k++) { // aca se hace ese recorrido, es mejor usar k para no alterar el valor del indice q es lo q al final se retorna
        if (vectorInicial.at(k) <= pivote) {
            swap(vectorInicial.at(k), vectorInicial.at(indice));
            indice++;
        }
    }
    swap(vectorInicial.at(indice), vectorInicial.at(right)); // Colocar el pivote en su posición correcta
    return indice; // Retornar la posición del pivote
}

void quickSort(vector<int>& vectorInicial, int left, int right) {
    if (left < right) {
        int pivote = dividir(vectorInicial, left, right);
        quickSort(vectorInicial, left, pivote - 1);  // Ordenar izquierda
        quickSort(vectorInicial, pivote + 1, right); // Ordenar derecha
    }
}

int main() {
    int size = 1000000;
    vector<int> vectorInicial;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 100);

    for (int i = 0; i < size; i++) {
        vectorInicial.push_back(distrib(gen));
    }

    /*
    cout << "Vector inicial: ";
    for (int num : vectorInicial) {
        cout << num << " ";
    }
    cout << endl;
    */

    auto inicio = chrono::high_resolution_clock::now(); // Iniciar medición de tiempo

    quickSort(vectorInicial, 0, vectorInicial.size() - 1);

    auto fin = chrono::high_resolution_clock::now(); // Fin de medición
    chrono::duration<double> duracion = fin - inicio;

    /*
    cout << "Vector organizado: ";
    for (int num : vectorInicial) {
        cout << num << " ";
    }
    cout << endl;
    */

    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

    return 0;
}
