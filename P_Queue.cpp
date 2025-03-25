#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class Queue{
    private:
    class Node{
        private:
        T data_;
        Node* next_;

        public:
        Node(const T& d){
            data_ = d;
            next_ = nullptr;
        }

        public:

        T& getData() {
            return data_;
        }

        const T& getData() const {
            return data_;
        }

        Node* getNext() const {
            return next_;
        }

        void setNext(Node* n){
            next_ = n;
        }
    };

    Node* front_;
    Node* back_;
    unsigned int size_;

    public:
    Queue(){
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }

    public:

    bool empty() const {
        return front_ == nullptr;
    }
    
    unsigned int size() const {
        return size_;
    }

    void enqueue(const T& d){
        Node* newNode = new Node(d);

        if (empty()){
            front_ = back_ = newNode;
        } else {
            back_->setNext(newNode);
            back_ = newNode;
        }
        size_++;
    }

    void dequeue(){
        assert(!empty());

        Node* temp = front_;
        front_ = front_->getNext();

        if (front_ == nullptr){
            back_ = nullptr;
        }

        delete temp;
        size_--;
    }

    T& front(){
        assert(!empty());

        return front_->getData();
    }

    const T& front() const {
        assert(!empty());

        return front_->getData();
    }

    void print() const {
        Node* current = front_;
        cout << "Front -> ";
        while (current != nullptr){
            cout << current->getData();
            if (current->getNext() != nullptr){
                cout << " -> ";
            }
            current = current->getNext();
        }
        cout << "<- Back" << endl;
    }

    

};


int main() {
    Queue<int> miCola;
    
    miCola.enqueue(10);
    miCola.enqueue(20);
    miCola.enqueue(30);
    
    miCola.print(); // Front -> 10 -> 20 -> 30 <- Back
    
    cout << "Front: " << miCola.front() << endl; // 10
    
    miCola.dequeue();
    miCola.print(); // Front -> 20 -> 30 <- Back
    
    miCola.enqueue(40);
    miCola.print(); // Front -> 20 -> 30 -> 40 <- Back
    
    return 0;
}