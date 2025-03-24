#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

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
        size_ = capacity_;
    }

    public:
    unsigned int size(){ // size
        return size_;
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

    private:
    void resize(){ // aumentar tamaño
        cout << "Resize" << endl;
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
        size_--;
    }

    void print(){ // imprimir 
        for (unsigned int i = 0 ; i < size_ ; i++){
            cout << " " << storage_[i];
        }
        cout << endl;
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
};

int main(){
    cout << "Vectors!" << endl;
    Vector<int> x(10, 0);
    
    x.print(); 
    x.push_back(5);
    x.print();
    x.push_front(5);
    x.print();
    x.pop_back();
    x.print();
    x.pop_front();
    x.print();

    return 0;
}