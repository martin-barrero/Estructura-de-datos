#include <iostream>
#include <cassert>

template <typename T>
class BST{
    private:
    class Node{
        private:
        T data_;
        Node* left_;
        Node* right_;

        public:
        Node(const T& d){
            data_ = d;
            left_ = nullptr;
            right_ = nullptr;
        }
    };

    Node* root_;

    public:
    BST(){
        root_ = nullptr;
    }

    public:

    void insert(const T& d){
        if (root_ == nullptr){
            root_ = new Node(d);
            return;
        }

        Node* current = root_;
        while (true){
            if (d < current->data_){
                if (current->left_ == nullptr){
                    current->left_ = new Node(d);
                    break;
                }
                current = current->left_;
            } else if (d > current->data_){
                if (current->right_ == nullptr){
                    current->right_ = new Node(d);
                    break;
                }
                current = current->right_;
            } else {
                // Valor duplicado
                break;
            }
        }
    }
};

int main (){
    return 0;
}