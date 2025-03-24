#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int dividir(vector<int>& vectorInicial, int left, int right){
    int pivote = vectorInicial.at(right);
    do {
        while (vectorInicial.at(left) < pivote){
            left++;
        }
        while (vectorInicial.at(right) > pivote){
            right--;
        }
        if (left <= right){ // Se verifica si no se han cruzado pq si ya lo hicieron entonces es pq en esa parte ya esta ordenado
            swap(vectorInicial.at(left), vectorInicial.at(right));
            left++;
            right--;
        }
    } while (left <= right);

    return left - 1; // IMPORTANTE (se retorna la posición final del pivote)
}

vector<int> quickSort(vector<int>& vectorInicial, int left, int right){
    if (left < right){
        int pivote = dividir(vectorInicial, left, right);
        quickSort(vectorInicial, left, pivote - 1); // Para ordenar la parte izquierda (se resta para no mover el pivote ps pq ya esta ordenado)
        quickSort(vectorInicial, pivote, right); // Para ordenar la parte derecha (no se suma porque el que se mueve el right)
    }
    
    return vectorInicial;
}

int main (){
    auto inicio = chrono::high_resolution_clock::now(); // Medición de tiempo de ejecución

    int size = 1000;
    vector<int> vectorInicial;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 100);

    for (int i = 0 ; i < size ; i++){
        vectorInicial.push_back(distrib(gen));
    }

    /*
    cout << "Vector inicial: ";0
    for (int i = 0 ; i < vectorInicial.size() ; i++){
        cout << vectorInicial.at(i) << " ";
    }
    cout << endl;
    */

    quickSort(vectorInicial, 0 , vectorInicial.size() - 1);

    /*
    cout << "Vector organizado: ";
    for (int i = 0 ; i < vectorInicial.size() ; i++){
        cout << vectorInicial.at(i) << " ";
    }
    cout << endl;
    */

    auto fin = chrono::high_resolution_clock::now(); // Medición de tiempo de ejecución
    chrono::duration<double> duracion = fin - inicio;
    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

    return 0;
}