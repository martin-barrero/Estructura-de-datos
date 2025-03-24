#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

void unir(vector<int>& vectorInicial, int left, int mitad, int right){
    int size1 = mitad - left + 1; // tamaño de la primera mitad (la suma es pa lo mismo, pa q no se repita el ultimo elemento)
    int size2 = right - mitad; // tamaño de la segunda mitad

    vector<int> vectorLeft(size1);
    vector<int> vectorRight(size2);

    // llenar las mitades
    // PREGUNTARLE AL PROFE PQ NO SE PUEDE USAR push_back
    for (int i = 0 ; i < size1 ; i++){
        vectorLeft[i] = vectorInicial[left + i];
    }
    for (int j = 0 ; j < size2 ; j++){
        vectorRight[j] = vectorInicial[mitad + 1 + j]; // tiene que empezar uno mas que la mitad pa q no se repita y se va moviendo
    }

    int i = 0, j = 0, k = left; // se duplica left pq se usa k como auxiliar

    while (i < size1 && j < size2){
        if (vectorLeft.at(i) <= vectorRight.at(j)){ // aca se meten en orden en el vector general
            vectorInicial.at(k) = vectorLeft.at(i);
            i++;
        } else {
            vectorInicial.at(k) = vectorRight.at(j);
            j++;
        }
        k++;
    }

    while (i < size1){ // si quedo algo en la izquierda se copian
        vectorInicial.at(k) = vectorLeft.at(i);
        i++;
        k++;
    }

    while (j < size2){ // lo mismo pero con la derecha
        vectorInicial.at(k) = vectorRight.at(j);
        j++;
        k++;
    }
}

void mergeSort(vector<int>& vectorInicial, int left, int right){
    if (left < right){
        int mitad = left + (right - left) / 2; // no se usa con size/2 pq se necesita el indice y no el valor
        mergeSort(vectorInicial, left, mitad); // se manda recursivamente la primera mitad
        mergeSort(vectorInicial, mitad + 1, right); // y aca lo mismo con la 2da mitad (el +1 es pa no repetir el ultimo del pasado)

        unir(vectorInicial, left, mitad, right); // se juntas las mitades
    }
}

int main (){
    auto inicio = chrono::high_resolution_clock::now(); // Medición de tiempo de ejecución

    int size = 10;
    vector<int> vectorInicial;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 100);

    for (int i = 0 ; i < size ; i++){
        vectorInicial.push_back(distrib(gen));
    }

    
    cout << "Vector inicial: ";
    for (int i = 0 ; i < vectorInicial.size() ; i++){
        cout << vectorInicial.at(i) << " ";
    }
    cout << endl;
    

    mergeSort(vectorInicial, 0, size - 1);

    
    cout << "Vector ordenado: ";
    for (int i = 0 ; i < vectorInicial.size() ; i++){
        cout << vectorInicial.at(i) << " ";
    }
    cout << endl;
    

    auto fin = chrono::high_resolution_clock::now(); // Medición de tiempo de ejecución
    chrono::duration<double> duracion = fin - inicio;
    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

    return 0;
}