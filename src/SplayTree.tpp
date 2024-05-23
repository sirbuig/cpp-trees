#ifndef TREES_SPLAYTREE_TPP
#define TREES_SPLAYTREE_TPP

#include "SplayTree.h"
#include <iostream>

template<typename T>
SplayTree<T>::SplayTree() : root(nullptr), size(0) {}

template<typename T>
SplayTree<T>::~SplayTree() {
    clear(root);
}

template<typename T>
void SplayTree<T>::clear(Node<T> *node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename T>
Node<T>* SplayTree<T>::findNode(const T& value) const {
    Node<T>* current = root;
    Node<T>* last = nullptr;

    while (current != nullptr) {
        last = current;
        if (current->data > value) {
            current = current->left;
        } else if (current->data < value) {
            current = current->right;
        } else {
            return current;
        }
    }

    if (last != nullptr) {
        const_cast<SplayTree<T>*>(this)->splay(last);
    }

    return nullptr;
}

template<typename T>
void SplayTree<T>::splay(Node<T>* node) {
    while (node->parent != nullptr) {
        if (node->parent == root) {
            if (node == node->parent->left) {
                rotateRight(node->parent);
            } else {
                rotateLeft(node->parent);
            }
        } else {
            Node<T>* parent = node->parent;
            Node<T>* grandparent = parent->parent;

            if (node == parent->left && parent == grandparent->left) {
                rotateRight(grandparent);
                rotateRight(parent);
            } else if (node == parent->right && parent == grandparent->right) {
                rotateLeft(grandparent);
                rotateLeft(parent);
            } else if (node == parent->right && parent == grandparent->left) {
                rotateLeft(parent);
                rotateRight(grandparent);
            } else {
                rotateRight(parent);
                rotateLeft(grandparent);
            }
        }
    }
    root = node;
}

template<typename T>
void SplayTree<T>::rotateRight(Node<T>* node) {
    Node<T>* leftChild = node->left;
    node->left = leftChild->right;
    if (node->left != nullptr) {
        node->left->parent = node;
    }

    leftChild->right = node;
    leftChild->parent = node->parent;

    if (node->parent != nullptr) {
        if (node == node->parent->left) {
            node->parent->left = leftChild;
        } else {
            node->parent->right = leftChild;
        }
    } else {
        root = leftChild;
    }

    node->parent = leftChild;
}

template<typename T>
void SplayTree<T>::rotateLeft(Node<T>* node) {
    Node<T>* rightChild = node->right;
    node->right = rightChild->left;
    if (node->right != nullptr) {
        node->right->parent = node;
    }

    rightChild->left = node;
    rightChild->parent = node->parent;

    if (node->parent != nullptr) {
        if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
    } else {
        root = rightChild;
    }

    node->parent = rightChild;
}

template<typename T>
Node<T>* SplayTree<T>::maximum(Node<T>* node) {
    Node<T>* current = node;
    while (current->right != nullptr) {
        current = current->right;
    }
    splay(current);
    return current;
}

template<typename T>
Node<T>* SplayTree<T>::minimum(Node<T>* node) {
    Node<T>* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    splay(current);
    return current;
}

template<typename T>
Node<T>* SplayTree<T>::successor(Node<T>* node) {
    if (node->right != nullptr) {
        return minimum(node->right);
    }
    Node<T>* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    splay(parent);
    return parent;
}

template<typename T>
Node<T>* SplayTree<T>::predecessor(Node<T>* node) {
    if (node->left != nullptr) {
        return maximum(node->left);
    }
    Node<T>* parent = node->parent;
    while (parent != nullptr && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    splay(parent);
    return parent;
}

template<typename T>
void SplayTree<T>::insert(const T& value) {
    if (findNode(value) == nullptr) {
        Node<T>* current = root;
        Node<T>* parent = nullptr;
        Node<T>* newNode = new Node<T>(value);

        ++size;

        while (current != nullptr) {
            parent = current;
            if (current->data > value) {
                current = current->left;
            } else {
                current = current->right;
            }
            newNode->parent = parent;
        }

        if (parent == nullptr) {
            root = newNode;
        } else {
            if (newNode->data < parent->data) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
            splay(newNode);
        }
    }
}

template<typename T>
void SplayTree<T>::remove(const T& value) {
    if (root != nullptr) {
        Node<T>* node = findNode(value);
        if (node != nullptr) {
            splay(node);
            if (root->left == nullptr) {
                root = root->right;
                delete node;
            } else {
                Node<T>* rightSubtree = root->right;
                root = root->left;
                delete node;
                root->parent = nullptr;
                Node<T>* maxLeftSubtree = maximum(root);
                splay(maxLeftSubtree);
                if (rightSubtree != nullptr) {
                    rightSubtree->parent = root;
                }
                root->right = rightSubtree;
            }
            --size;
        }
    }
}

template<typename T>
bool SplayTree<T>::find(const T& value) const {
    Node<T>* node = findNode(value);
    if (node != nullptr) {
        const_cast<SplayTree<T>*>(this)->splay(node);
        return true;
    }
    return false;
}

template<typename T>
void SplayTree<T>::print() const {
    printInOrder(root);
    std::cout << std::endl;
}

template<typename T>
void SplayTree<T>::print(T X, T Y) const {
    printInRange(root, X, Y);
    std::cout << std::endl;
}

template<typename T>
void SplayTree<T>::printInOrder(Node<T>* node) const {
    if (node == nullptr) {
        return;
    }
    printInOrder(node->left);
    std::cout << node->data << " ";
    printInOrder(node->right);
}

template<typename T>
void SplayTree<T>::printInRange(Node<T>* node, T X, T Y) const {
    if (node == nullptr) {
        return;
    }
    printInRange(node->left, X, Y);
    if (node->data >= X && node->data <= Y) {
        std::cout << node->data << " ";
    }
    printInRange(node->right, X, Y);
}

template<typename T>
T SplayTree<T>::findPredecessor(const T& value) {
    Node<T>* node = findNode(value);
    if (node == nullptr) {
        return T();
    }
    Node<T>* predNode = predecessor(node);
    if (predNode != nullptr) {
        return predNode->data;
    }
    return T();
}

template<typename T>
T SplayTree<T>::findSuccessor(const T& value) {
    Node<T>* node = findNode(value);
    if (node == nullptr) {
        return T();
    }
    Node<T>* succNode = successor(node);
    if (succNode != nullptr) {
        return succNode->data;
    }
    return T();
}

template<typename T>
Node<T>* SplayTree<T>::lte_max(Node<T>* node, const T& value) {
    Node<T>* result = nullptr;
    while (node) {
        if (node->data <= value) {
            if (!result || node->data > result->data)
                result = node;
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return result;
}

template<typename T>
Node<T>* SplayTree<T>::mte_min(Node<T>* node, const T& value) {
    Node<T>* result = nullptr;
    while (node) {
        if (node->data >= value) {
            result = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return result;
}

template<typename T>
Node<T>* SplayTree<T>::lte_max(const T& value) {
    return lte_max(root, value);
}

template<typename T>
Node<T>* SplayTree<T>::mte_min(const T& value) {
    return mte_min(root, value);
}

#endif //TREES_SPLAYTREE_TPP
