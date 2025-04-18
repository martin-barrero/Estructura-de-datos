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

template <typename T>
class DLL {
    private:
        class Node {
            private:
            T data_;
            Node* next_;
            Node* prev_;
    
            public:
            Node() {
                data_ = T();
                prev_ = next_ = nullptr;
            }
    
            Node(const T& d) {
                data_ = d;
                prev_ = next_ = nullptr;
            }
    
            T getData() const {
                return data_;
            }
    
            Node* getNext() const {
                return next_;
            }
    
            Node* getPrev() const {
                return prev_;
            }
    
            void setNext(Node *nxt) {
                next_ = nxt;
            }
    
            void setPrev(Node *prv) {
                prev_ = prv;
            }
    
            void setData(const T& data) {
                data_ = data;
            }
        }; 
    
    private:
        Node *first_;
        Node *last_;
        unsigned int size_;
    
    public:
        DLL() {
            first_ = last_ = nullptr;
            size_ = 0;
        }
    
        bool empty() const {
            return first_ == nullptr;
        }
    
        unsigned int size() const {
            return size_;
        }
    
        void print() {
            Node* current = first_;
            while (current != nullptr)
            {
                cout << current->getData() << " -> ";
                current = current->getNext();
            }
        cout << "nullptr" << endl;
        }
    
        void push_front(const T& d) {
            Node *n = new Node(d);
    
            n->setNext(first_);
    
            if (first_ != nullptr) {
                first_->setPrev(n);  
            }
    
            first_ = n;
            
            if (size_ == 0)
            {
                last_ = n;
            }
            
            size_++;
        }

        void push_back(const T& d) {
            Node* n = new Node(d);
            
            if (empty()) {
                first_ = last_ = n;
            } else {
                last_->setNext(n);
                n->setPrev(last_);
                last_ = n;
            }
            
            size_++;
        }
    
        void insert(const T& d, unsigned int pos) {
            assert(pos <= size_);  // Posición debe ser válida
            
            if (pos == 0) {
                push_front(d);
                return;
            }
            
            if (pos == size_) {
                push_back(d);
                return;
            }
            
            Node* n = new Node(d);
            Node* current = first_;
            
            // Avanzar hasta la posición deseada
            for (unsigned int i = 0; i < pos; i++) {
                current = current->getNext();
            }
            
            // Enlazar el nuevo nodo
            n->setPrev(current->getPrev());
            n->setNext(current);
            current->getPrev()->setNext(n);
            current->setPrev(n);
            
            size_++;
        }
    
        void pop_front() {
            assert(!empty());
            
            Node* temp = first_;
            first_ = first_->getNext();
            
            if (first_ != nullptr) {
                first_->setPrev(nullptr);
            } else {
                last_ = nullptr;  // Lista quedó vacía
            }
            
            delete temp;
            size_--;
        }
    
        void pop_back() {
            assert(!empty());
            
            if (size_ == 1) {
                pop_front();
                return;
            }
            
            Node* temp = last_;
            last_ = last_->getPrev();
            last_->setNext(nullptr);
            
            delete temp;
            size_--;
        }
    
        // Método adicional útil para DLL: imprimir en orden inverso
        void print_reverse() {
            Node* current = last_;
            while (current != nullptr) {
                cout << current->getData() << " -> ";
                current = current->getPrev();
            }
            cout << "nullptr" << endl;
        }
    
};

template <typename T>
class CDLL {
private:
    class Node {
    private:
        T data_;
        Node* next_;
        Node* prev_;

    public:
        Node() {
            data_ = T();
            prev_ = next_ = nullptr;
        }

        Node(const T& d) {
            data_ = d;
            prev_ = next_ = nullptr;
        }

        T getData() const {
            return data_;
        }

        Node* getNext() const {
            return next_;
        }

        Node* getPrev() const {
            return prev_;
        }

        void setNext(Node* nxt) {
            next_ = nxt;
        }

        void setPrev(Node* prv) {
            prev_ = prv;
        }

        void setData(const T& data) {
            data_ = data;
        }
    };

private:
    Node* head_;  // Puntero al nodo cabeza (puede ser cualquier nodo)
    unsigned int size_;

public:
    CDLL() {
        head_ = nullptr;
        size_ = 0;
    }

    bool empty() const {
        return head_ == nullptr;
    }

    unsigned int size() const {
        return size_;
    }

    void push_front(const T& d) {
        Node* n = new Node(d);
        
        if (empty()) {
            n->setNext(n);
            n->setPrev(n);
            head_ = n;
        } else {
            Node* last = head_->getPrev();
            
            n->setNext(head_);
            n->setPrev(last);
            
            head_->setPrev(n);
            last->setNext(n);
            
            head_ = n;
        }
        
        size_++;
    }

    void push_back(const T& d) {
        // En una lista circular, push_back es similar a push_front pero no se mueve el head
        Node* n = new Node(d);
        
        if (empty()) {
            n->setNext(n);
            n->setPrev(n);
            head_ = n;
        } else {
            Node* last = head_->getPrev();
            
            n->setNext(head_);
            n->setPrev(last);
            
            head_->setPrev(n);
            last->setNext(n);
        }
        
        size_++;
    }

    void insert(const T& d, unsigned int pos) {
        assert(pos <= size_);
        
        if (pos == 0) {
            push_front(d);
            return;
        }
        
        if (pos == size_) {
            push_back(d);
            return;
        }
        
        Node* n = new Node(d);
        Node* current = head_;
        
        for (unsigned int i = 0; i < pos; i++) {
            current = current->getNext();
        }
        
        Node* prev = current->getPrev();
        
        n->setNext(current);
        n->setPrev(prev);
        
        prev->setNext(n);
        current->setPrev(n);
        
        size_++;
    }

    void pop_front() {
        assert(!empty());
        
        if (size_ == 1) {
            delete head_;
            head_ = nullptr;
        } else {
            Node* new_head = head_->getNext();
            Node* last = head_->getPrev();
            
            new_head->setPrev(last);
            last->setNext(new_head);
            
            delete head_;
            head_ = new_head;
        }
        
        size_--;
    }

    void pop_back() {
        assert(!empty());
        
        if (size_ == 1) {
            pop_front();
            return;
        }
        
        Node* last = head_->getPrev();
        Node* new_last = last->getPrev();
        
        new_last->setNext(head_);
        head_->setPrev(new_last);
        
        delete last;
        size_--;
    }

    void print() {
        if (empty()) {
            cout << "Lista vacía" << endl;
            return;
        }
        
        Node* current = head_;
        do {
            cout << current->getData();
            current = current->getNext();
            if (current != head_) {
                cout << " <-> ";
            }
        } while (current != head_);
        
        cout << " (circular)" << endl;
    }

    void print_reverse() {
        if (empty()) {
            cout << "Lista vacía" << endl;
            return;
        }
        
        Node* current = head_->getPrev();
        Node* start = current;
        
        do {
            cout << current->getData();
            current = current->getPrev();
            if (current != start) {
                cout << " <-> ";
            }
        } while (current != start);
        
        cout << " (circular inversa)" << endl;
    }
};

int main (){
    return 0;
}