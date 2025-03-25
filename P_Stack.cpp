#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class Stack{
    private:
    class Node{
        private:
        T data_;
        Node *next_;

        public:
        Node(const T& d, Node *n = nullptr){
            data_ = d;
            next_ = n;
        }

        // Metodos de acceso
        T& getData(){
            return data_;
        }

        const T& getData() const {  // Versión constante
            return data_;
        }

        Node* getNext() const{
            return next_;
        }

        void setNext(Node* n){
            next_ = n;
        }
    };

    Node* top_;
    unsigned int size_;

    public:
    Stack(){
        top_ = nullptr;
        size_ = 0;
    }

    public:
    bool empty() const{
        return top_ == nullptr;
    }

    unsigned int size() const {
        return size_;
    }

    void push(const T& d){
        top_ = new Node(d, top_);
        size_++;
    }

    void pop(){
        assert(!empty());

        Node* temp = top_;
        top_ = top_->getNext();
        delete temp;
        size_--;
    }

    T& top(){
        assert(!empty());

        return top_->getData();
    }

    const T& top() const{
        assert(empty());
        
        return top_->getData();
    }

    void print() const{
        Node* current = top_;
        cout << "Top -> ";
        while (current != nullptr){
            cout << current->getData() << " -> ";
            current = current->getNext();
        }
        cout << "Bottom" << endl;
    }
};

int main() {
    Stack<int> miPila;
    
    miPila.push(10);
    miPila.push(20);
    miPila.push(30);
    
    miPila.print(); // Top -> 30 -> 20 -> 10 -> Bottom
    
    cout << "Top: " << miPila.top() << endl; // 30
    
    miPila.pop();
    miPila.print(); // Top -> 20 -> 10 -> Bottom
    
    return 0;
}