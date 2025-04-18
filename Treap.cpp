#include <iostream>
#include <random>
#include <ctime>
#include <cassert>

using namespace std;

template <typename T>
class Treap {
private:
    class Node {
    public:
        T element_;
        int priority_;
        Node* left_;
        Node* right_;

        Node() : element_(T()), priority_(rand() % 100), left_(nullptr), right_(nullptr) {}
        Node(const T& e) : element_(e), priority_(rand() % 100), left_(nullptr), right_(nullptr) {}
    };

    Node* root_;

    // Rotación derecha
    void rotateRight(Node*& parentNode) {
        Node* newParent = parentNode->left_;
        Node* orphanSubtree = newParent->right_;
        
        parentNode->left_ = orphanSubtree;
        newParent->right_ = parentNode;
        parentNode = newParent;
    }

    // Rotación izquierda
    void rotateLeft(Node*& parentNode) {
        Node* newParent = parentNode->right_;
        Node* orphanSubtree = newParent->left_;
        
        parentNode->right_ = orphanSubtree;
        newParent->left_ = parentNode;
        parentNode = newParent;
    }

    void insertNode(Node*& currentNode, const T& newValue) {
        if (currentNode == nullptr) {
            currentNode = new Node(newValue);
            return;
        }

        if (newValue <= currentNode->element_) {
            insertNode(currentNode->left_, newValue);
            if (currentNode->left_->priority_ > currentNode->priority_) {
                rotateRight(currentNode);
            }
        } else {
            insertNode(currentNode->right_, newValue);
            if (currentNode->right_->priority_ > currentNode->priority_) {
                rotateLeft(currentNode);
            }
        }
    }

    void deleteNode(Node*& currentNode, const T& valueToRemove) {
        if (currentNode == nullptr) return;

        if (valueToRemove < currentNode->element_) {
            deleteNode(currentNode->left_, valueToRemove);
        } else if (valueToRemove > currentNode->element_) {
            deleteNode(currentNode->right_, valueToRemove);
        } else {
            // Caso 1: Nodo hoja
            if (currentNode->left_ == nullptr && currentNode->right_ == nullptr) {
                delete currentNode;
                currentNode = nullptr;
            }
            // Caso 2: Solo hijo derecho
            else if (currentNode->left_ == nullptr) {
                Node* temp = currentNode;
                currentNode = currentNode->right_;
                delete temp;
            }
            // Caso 3: Solo hijo izquierdo
            else if (currentNode->right_ == nullptr) {
                Node* temp = currentNode;
                currentNode = currentNode->left_;
                delete temp;
            }
            // Caso 4: Ambos hijos
            else {
                if (currentNode->left_->priority_ > currentNode->right_->priority_) {
                    rotateRight(currentNode);
                    deleteNode(currentNode->right_, valueToRemove);
                } else {
                    rotateLeft(currentNode);
                    deleteNode(currentNode->left_, valueToRemove);
                }
            }
        }
    }

    bool contains(Node* currentNode, const T& searchValue) const {
        if (currentNode == nullptr) return false;
        if (currentNode->element_ == searchValue) return true;
        return contains(searchValue < currentNode->element_ ? currentNode->left_ : currentNode->right_, searchValue);
    }

    void inOrderTraversal(Node* currentNode) const {
        if (currentNode == nullptr) return;
        inOrderTraversal(currentNode->left_);
        cout << currentNode->element_ << "(" << currentNode->priority_ << ") ";
        inOrderTraversal(currentNode->right_);
    }

    void clearTree(Node* currentNode) {
        if (currentNode == nullptr) return;
        clearTree(currentNode->left_);
        clearTree(currentNode->right_);
        delete currentNode;
    }

public:
    Treap() : root_(nullptr) {
        srand(time(nullptr));
    }

    ~Treap() {
        clearTree(root_);
    }

    void insert(const T& value) {
        insertNode(root_, value);
    }

    void remove(const T& value) {
        deleteNode(root_, value);
    }

    bool contains(const T& value) const {
        return contains(root_, value);
    }

    void printInOrder() const {
        inOrderTraversal(root_);
        cout << endl;
    }

    bool empty() const {
        return root_ == nullptr;
    }
};

int main() {
    Treap<int> treap;

    // Insertar elementos
    cout << "Insertando elementos: 50, 30, 20, 40, 70, 60, 80\n";
    treap.insert(50);
    treap.insert(30);
    treap.insert(20);
    treap.insert(40);
    treap.insert(70);
    treap.insert(60);
    treap.insert(80);

    // Mostrar árbol
    cout << "Treap (in-order): ";
    treap.printInOrder();

    // Buscar elementos
    cout << "\nBusquedas:\n";
    cout << "Contiene 40? " << (treap.contains(40) ? "Si" : "No") << endl;
    cout << "Contiene 25? " << (treap.contains(25) ? "Si" : "No") << endl;

    // Eliminar nodo hoja (20)
    cout << "\nEliminando 20 (nodo hoja)\n";
    treap.remove(20);
    cout << "Treap despues de eliminar: ";
    treap.printInOrder();

    // Eliminar nodo con un hijo (30)
    cout << "\nEliminando 30 (nodo con un hijo)\n";
    treap.remove(30);
    cout << "Treap despues de eliminar: ";
    treap.printInOrder();

    // Eliminar nodo con dos hijos (50)
    cout << "\nEliminando 50 (nodo con dos hijos)\n";
    treap.remove(50);
    cout << "Treap despues de eliminar: ";
    treap.printInOrder();

    // Verificación final
    cout << "\nVerificacion final:\n";
    int valores[] = {20, 30, 40, 50, 60, 70, 80};
    for (int val : valores) {
        cout << "Contiene " << val << "? " << (treap.contains(val) ? "Si" : "No") << endl;
    }

    return 0;
}