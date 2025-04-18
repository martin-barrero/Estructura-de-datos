#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;

template <typename T>
class BST {
    private:
    class Node {
        private:
        T element_;
        Node* right_;
        Node* left_;

        public:
        Node(){
            element_ = T();
            right_ = nullptr;
            left_ = nullptr;
        }

        Node(const T& e){
            element_ = e;
            right_ = nullptr;
            left_ = nullptr;
        }

        public:
        T getElement() const {
            return element_;
        }

        void setElement(const T& e){
            element_ = e;
        }

        Node* getLeft() const {
            return left_;
        }

        void setLeft(Node* l){
            left_ = l;
        }

        Node* getRight() const {
            return right_;
        }

        void setRight(Node* r){
            right_ = r;
        }
    };

    private:
    Node* root_;
    unsigned int size_;

    public:
    BST(){
        root_ = nullptr;
        size_ = 0;
    }

    BST(const T& e){
        root_ = new Node(e);
        size_ = 1;
    }

    private:
    bool find(Node* node, const T& data){
        if (!node){
            return false;
        }
        if (data == node->getElement()){
            return true;
        }
        if (data < node->getElement()) {
            return find(node->getLeft(), data);  // Buscar en el subárbol izquierdo
        } else {
            return find(node->getRight(), data);  // Buscar en el subárbol derecho
        }
        
    }

    Node* insert(Node* node, T value) {
        if (!node) return new Node(value);  // Si el nodo es nulo, insertamos el nuevo nodo
    
        if (value < node->getElement()) {
            node->setLeft(insert(node->getLeft(), value));  // Insertamos en el subárbol izquierdo
        } else {
            node->setRight(insert(node->getRight(), value));  // Insertamos en el subárbol derecho
        }
        return node;
    }

    public:
    unsigned int size() const {
        return size_;
    }

    Node* root() const {
        return root_;
    }

    void insert(const T& element) { 
        // Si el elemento no está en el árbol, lo insertamos
        if (!find(root_, element)){  // Encuentra si el elemento ya existe
            root_ = insert(root_, element);  // Inserta el elemento
            size_++;  // Aumenta el tamaño del árbol
        }
    }

    void inOrder(Node* node){
        assert(root_!= nullptr);
        if (node != nullptr){
            inOrder(node->getLeft()); // Se va por la izquierda 
            cout << node->getElement() << " ";
            inOrder(node->getRight()); // Se va por la derecha
        }
    }

    void preOrder(Node* node){
        assert(root_ != nullptr);
        if(node != nullptr){
            cout << node->getElement() << " "; // Primero la raiz
            preOrder(node->getLeft()); // dsp toda la izquierda
            preOrder(node->getRight()); // y dsp toda la derecha
        }
    }

    void postOrder(Node* node){
        assert(root_ != nullptr);
        if(node != nullptr){
            postOrder(node->getLeft()); // Primero la izquierda
            postOrder(node->getRight()); // dsp la derecha
            cout << node->getElement() << " "; // ulrimo la raiz
        }
    }

    Node* findMin(Node* node) { // el menor siempre va a ser el ultimo de la izquierda
        assert(node != nullptr);
        while (node->getLeft()) {
            node = node->getLeft();
        }
        return node;
    }

    Node* remove(Node* node, const T& data_){
        assert(size_ != 0);
            if(!node){
                return nullptr;
            }
            if(data_ < node->getElement()){
                node->setLeft(remove(node->getLeft(), data_));
            } else if (data_ > node->getElement()){
                node->setRight(remove(node->getRight(), data_)); 
            } else {
                if (!node->getLeft() || !node->getRight()) { // Si es el primer hijo
                    Node* temp;
                    if (node->getLeft()) {
                        temp = node->getLeft();  // Si hay un hijo izquierdo, lo asignamos a temp
                    } else {
                        temp = node->getRight();  // Si no hay hijo izquierdo, asignamos el hijo derecho a temp
                    }
                    delete node;  // Eliminamos el nodo actual
                    return temp;
                }
                Node* minNode = findMin(node->getRight()); // Encontrar el sucesor mínimo en el subárbol derecho
                node->setElement(minNode->getElement()); // Copiar el valor del sucesor mínimo al nodo actual
                node->setRight(remove(node->getRight(), minNode->getElement())); // Eliminar el sucesor mínimo en el subárbol derecho, pq ya se copio al nodo que estamos eliminando
            }
            return node;
    }
};

int main (){
    BST<int> bst;

    // Insertar algunos elementos
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Mostrar el árbol en diferentes órdenes
    cout << "In-order traversal: ";
    bst.inOrder(bst.root());
    cout << endl;

    cout << "Pre-order traversal: ";
    bst.preOrder(bst.root());
    cout << endl;

    cout << "Post-order traversal: ";
    bst.postOrder(bst.root());
    cout << endl;
    
    // Eliminar un nodo y mostrar el árbol de nuevo
    bst.remove(bst.root(), 50);
    
    cout << "In-order traversal after removal: ";
    bst.inOrder(bst.root());
    cout << endl;

    return 0;
}