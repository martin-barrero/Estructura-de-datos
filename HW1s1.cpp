#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

template <typename T>
class Vector{
    private:
    T* storage_;
    unsigned int size_;
    unsigned int capacity_;

    public:
    Vector(){
        capacity_ = 5;
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Vector(unsigned int c, T elem){
        capacity_ = c;
        storage_ = new T[capacity_];
        for (unsigned int i = 0 ; i < capacity_ ; i++){
            storage_[i] = elem;
        }
        size_ = 0;
    }

    Vector(unsigned int c){
        size_ = c;
        capacity_ = size_;
        storage_ = new T[size_];

        for (unsigned int i = 0; i < size_; i++) {
            storage_[i] = 0;
        }
        
    }

    Vector(initializer_list<T> initList){
        capacity_ = initList.size();
        storage_ = new T[capacity_];
        size_ = 0;

        for (const T& elem : initList){ // ciclo bucle que llena el vector
            storage_[size_++] = elem;
        }
    }

    public:
    unsigned int size() const { // size
        return size_;
    }

    unsigned int capacity() const {
        return capacity_;
    }

    void print() const { // imprimir 
        cout << "{";
        for (unsigned int i = 0 ; i < size_ ; i++){
            cout << " " << storage_[i];
        }
        cout << " }" << endl;
    }

    T& at(unsigned int pos){ // at 1
        assert(pos >= 0 && pos < size_); 
        return storage_[pos];
    }

    const T& at(unsigned int pos) const { // at 2
        assert(pos >= 0 && pos < size_);
        return storage_[pos];
    }

    const T& operator[](unsigned int index) const { // at 3 (con ubicación de [])
        return storage_[index];
    }

    bool empty(){ // Verificar si está vacio 
        return size_ == 0;
    }

    private:
    void resize(){ // aumentar tamaño
        // cout << "Resize" << endl;
        unsigned int capacity2 = capacity_ * 1.5;
        T* storage_2 = new T[capacity2];
        for (unsigned int i = 0 ; i < size_ ; i++){
            storage_2[i] = storage_[i];
        }
        delete[] storage_;
        storage_ = storage_2;
        capacity_ = capacity2;
    }

    public:
    void push_back(const T& elem){ // añadir elemento al final
        if (size_ == capacity_){
            resize();
        }
        storage_[size_] = elem;
        size_++;
    }

    void pop_back(){ // eliminar un elemento al final
        assert(size_ > 0);
        size_--;
    }

    void push_front(const T& elem){ // añadir un elemento al inicio
        if (size_ == capacity_){
            resize();
        }
        for (unsigned int i = size_; i > 0 ; i--){
            storage_[i] = storage_[i - 1];
        }
        storage_[0] = elem;
        size_++;
    }

    void pop_front(){ // quitar el primer numero
        assert(size_ > 0);

        for (unsigned int i = 0 ; i < size_ - 1; i++){
            storage_[i] = storage_[i + 1];
        }
        size_--;
    }

    unsigned int waste(){ // Capacidad sin usar
        unsigned int w = capacity_ - size_;
        return w;
    }

    void release(){ // shrink to fit
        assert(waste() > 0);

        T* storage_2 = new T[size_];
        for (unsigned int i = 0 ; i < size_ ; i++){
            storage_2[i] = storage_[i];
        }
        delete[] storage_;
        storage_ = storage_2;
        capacity_ = size_;
    }
    
    void insert(unsigned int pos, const T& elem){ // Insertar un elemento en x posición (remplanzando el que ya estaba)
        assert(0 <= pos && pos < size_);

        if (size_ == capacity_){
            resize();
        }
        for (unsigned int i = size_; i > pos ; i--) {
            storage_[i] = storage_[i - 1];
        }
        storage_[pos] = elem;
    }

    void erase(unsigned int pos){ // Borrar determinado elemento
        assert ((0 <= pos) && (pos < size_));

        for (unsigned int i = pos; i < size_ - 1; i++) {
            storage_[i] = storage_[i + 1];
        }
        size_--;
    }

    void remove_duplicates(){
        unsigned int i = 0;
        while (i < size_){
            unsigned int j = i + 1;
            while (j < size_){
                if (storage_[i] == storage_[j]){
                    erase(j);
                } else {
                    j++;
                }
            }
            i++;
        }
    }

    private:
    void mergeP(int left, int mid, int right) {
        int size1 = mid - left + 1; // Size of the first half
        int size2 = right - mid;    // Size of the second half

        T* leftArray = new T[size1];
        T* rightArray = new T[size2];

        for (int i = 0; i < size1; i++) {
            leftArray[i] = storage_[left + i];
        }
        for (int j = 0; j < size2; j++) {
            rightArray[j] = storage_[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;
        while (i < size1 && j < size2) {
            if (leftArray[i] <= rightArray[j]) {
                storage_[k] = leftArray[i];
                i++;
            } else {
                storage_[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < size1) {
            storage_[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < size2) {
            storage_[k] = rightArray[j];
            j++;
            k++;
        }

        delete[] leftArray;
        delete[] rightArray;
    }

    void mergeSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(left, mid);
            mergeSort(mid + 1, right);

            mergeP(left, mid, right);
        }
    }

public:
    void sort() {
        if (size_ > 1) {
            mergeSort(0, size_ - 1);
        }
    }

    bool isSorted() const {
        if (size_ <= 1) {
            return true;
        }
        
        for (unsigned int i = 0; i < size_ - 1; i++) {
            if (storage_[i] > storage_[i + 1]) {
                return false;
            }
        }

        return true;
    }
};

template <typename T>
class Stack{
    private:
    Vector<T> vecStack;

    public:
    Stack() = default; // COnstructor por defecto pq usa el mismo del Vector

    unsigned int size() const {
        return vecStack.size();
    }

    void push(const T& elem){
        vecStack.push_back(elem);
    }

    void pop(){
        vecStack.pop_back();
    }

    bool empty(){
        return vecStack.empty();
    }

    T& top(){
        assert(!vecStack.empty());

        return vecStack.at(vecStack.size() - 1);
    }

    void print(){
        for (int i = vecStack.size() - 1; i >= 0; i--) {
            cout << "| " << vecStack.at(i) << " |" << endl;
        }
    }
};

template <typename T>
Vector<T> mergeSortedVectors(const Vector<T>& vec1, const Vector<T>& vec2) {
    Vector<T> mergedVector;

    unsigned int i = 0, j = 0;

    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i] <= vec2[j]) {
            mergedVector.push_back(vec1[i++]);
        } else {
            mergedVector.push_back(vec2[j++]);
        }
    }

    while (i < vec1.size()) {
        mergedVector.push_back(vec1[i++]);
    }

    while (j < vec2.size()) {
        mergedVector.push_back(vec2[j++]);
    }

    return mergedVector;
}

int main() {
    Vector<int> myVector = {20, 10, 30, 40, 50, 90, 70};
    cout << "Is sorted?: " << myVector.isSorted() << endl;
    myVector.sort();
    myVector.print();
    cout << "Is sorted?: " << myVector.isSorted() << endl << endl;

    Vector<int> vector1 = {1, 3, 5};
    Vector<int> vector2 = {2, 4, 6};
    Vector<int> mergedVector = mergeSortedVectors(vector1, vector2);
    mergedVector.print();

    Vector<int> vector3 = {1, 2, 3};
    Vector<int> vector4 = {};
    Vector<int> mergedVector2 = mergeSortedVectors(vector3, vector4);
    mergedVector2.print();

    Vector<int> vector5 = {};
    Vector<int> vector6 = {4,5,6};
    Vector<int> mergedVector3 = mergeSortedVectors(vector5, vector6);
    mergedVector3.print();

    Vector<int> vector7 = {1,1,1,1};
    Vector<int> vector8 = {1,1,1,1};
    Vector<int> mergedVector4 = mergeSortedVectors(vector7, vector8);
    mergedVector4.print();

    return 0;
}