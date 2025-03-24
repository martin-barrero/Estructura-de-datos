#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Función para fusionar dos mitades ordenadas del vector
void merge(vector<int> &vec, int izq, int medio, int der) {
    int n1 = medio - izq + 1; // Tamaño de la primera mitad
    int n2 = der - medio;     // Tamaño de la segunda mitad

    // Vectores temporales para almacenar las mitades
    vector<int> izquierda(n1);
    vector<int> derecha(n2);

    // Copiamos los elementos a los vectores temporales
    for (int i = 0; i < n1; i++)
        izquierda[i] = vec[izq + i];
    for (int j = 0; j < n2; j++)
        derecha[j] = vec[medio + 1 + j];

    int i = 0, j = 0, k = izq;

    // Fusionamos las mitades comparando los elementos
    while (i < n1 && j < n2) {
        if (izquierda[i] <= derecha[j]) {
            vec[k] = izquierda[i];
            i++;
        } else {
            vec[k] = derecha[j];
            j++;
        }
        k++;
    }

    // Copiamos los elementos restantes de izquierda (si quedaron)
    while (i < n1) {
        vec[k] = izquierda[i];
        i++;
        k++;
    }

    // Copiamos los elementos restantes de derecha (si quedaron)
    while (j < n2) {
        vec[k] = derecha[j];
        j++;
        k++;
    }
}

// Función Merge Sort para ordenar el vector
void mergeSort(vector<int> &vec, int izq, int der) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2; // Punto medio

        // Ordenamos la primera mitad
        mergeSort(vec, izq, medio);
        // Ordenamos la segunda mitad
        mergeSort(vec, medio + 1, der);

        // Fusionamos ambas mitades ordenadas
        merge(vec, izq, medio, der);
    }
}

int main() {
    int size = 10;
    vector<int> vectorInicial;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 100);

    // Llenamos el vector con números aleatorios
    for (int i = 0; i < size; i++) {
        vectorInicial.push_back(distrib(gen));
    }

    // Mostramos el vector antes de ordenar
    cout << "Vector inicial: ";
    for (int i = 0; i < vectorInicial.size(); i++) {
        cout << vectorInicial[i] << " ";
    }
    cout << endl;

    // Aplicamos Merge Sort
    mergeSort(vectorInicial, 0, size - 1);

    // Mostramos el vector después de ordenar
    cout << "Vector ordenado: ";
    for (int i = 0; i < vectorInicial.size(); i++) {
        cout << vectorInicial[i] << " ";
    }
    cout << endl;

    return 0;
}
