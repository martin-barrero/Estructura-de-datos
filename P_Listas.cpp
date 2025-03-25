#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class SLL{

    private:
    class Node{
        private:
        T data_;
        Node* next_;

        public:
        Node(){
            data_ = T();
            next_ = nullptr;
        }

        Node(const T& d){
            data_ = d;
            next_ = nullptr;
        }

        public:
        T getData() const {
            return data_;
        }

        Node* getNext() const{
            return next_;
        }

        void setNext(Node* nxt){
            next_ = nxt;
        }

        void setData(const T& data){
            data_ = data;
        }
    };

    private:
    Node *first_;
    Node *last_;
    unsigned int size_;

    public:
    SLL(){
        first_ = nullptr;
        last_ = nullptr;
        size_ = 0;
    }

    public:

    bool empty() const{
        return first_ == nullptr;
    }

    unsigned int size() const{
        return size_;
    }

    void push_front(const T& d){
        Node *n = new Node(d); // Nuevo nodo con valor de d
        n->setNext(first_); // hace que el nuevo nodo apunte al que apuntaba firts_
        first_ = n; // hace que firts apunte a n

        if(size_ == 0){ // Para la lista vacía
            last_ = n;
        }

        size_++;
    }

    void push_back(const T& d){
        Node *n = new Node(d);

        if (empty()){
            first_ = n;
            last_ = n; // ambos apuntan a el nuevo nodo
        } else {
            last_->setNext(n); // el ultimo se enlaza con el nuevo
            last_ = n; // se actualiza este puntero para que apunte al nuevo
        }

        size_++;
    }

    void insert(const T& d, unsigned int pos){
        Node* n = new Node(d);

        assert(pos > size_);

        if (pos == 0){
            push_front(d);
        }

        Node *current = first_;
        for (unsigned int i = 0 ; i < pos - 1 ; i++){
            current = current->getNext(); // avanza a la posicion deseada
        }

        n->setNext(current->getNext()); // n apunta al siguiente nodo despues de current
        current->setNext(n); // current apunta al nuevo nodo n

        if (n->getNext() == nullptr){
            last_ = n;
        }

        size_++;
    }

    void pop_front(){
        assert(empty());

        Node *temp = first_;
        first_ = first_->getNext();

        delete temp;

        if (first_ == nullptr) {
            last_ = nullptr;
        }
    
        size_--;
    }

    void pop_back(){
        assert(empty());

        if (first_->getNext() == nullptr) { // Si solo hay un elemento en la lista.
            pop_front();
            return;
        }
    
        Node *current = first_;
        while (current->getNext()->getNext() != nullptr) { // Recorremos hasta el penúltimo nodo.
            current = current->getNext();
        }

        delete current->getNext(); // Eliminamos el último nodo.
        current->setNext(nullptr); // El penúltimo nodo ahora es el último.
    
        last_ = current; // Actualizamos `last_` al nuevo último nodo.
        size_--; // Reducimos el tamaño de la lista.
    }

    void print() {
        Node *current = first_;
        while (current != nullptr)
        {
            cout << current->getData() << " -> ";
            current = current->getNext();   
        }
    cout << "nullptr" << endl;
    }
};

int main (){
    return 0;
}