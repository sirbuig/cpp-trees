#pragma once
#include "../include/Treap.h"

template<typename T>
Treap<T>::Treap() : root(nullptr) {}

template<typename T>
Treap<T>::~Treap() {
    clear(root);
}

template<typename T>
void Treap<T>::insert(const T &value) {
    root = insert(root, value);
}

template<typename T>
Node<T> *Treap<T>::insert(Node<T> *node, T value) {
    if(!node)
        return new Node<T>(value);

    if(value < node->data) {
        node->left = insert(node->left, value);
        if(node->left->priority > node->priority)
            node = right_rotate(node);
    } else {
        node->right = insert(node->right, value);
        if(node->right->priority > node->priority)
            node = left_rotate(node);
    }
    return node;
}

template<typename T>
void Treap<T>::remove(const T &value) {
    root = remove(root, value);
}

template<typename T>
Node<T> *Treap<T>::remove(Node<T> *node, T value) {
    if(!node)
        return nullptr;

    if(value < node->data)
        node->left = remove(node->left, value);
    else if(value > node->data)
        node->right = remove(node->right, value);
    else {
        if(!node->left) {
            Node<T> *temp = node->right;
            delete node;
            node = temp;
        } else if(!node->right) {
            Node<T> *temp = node->left;
            delete node;
            node = temp;
        } else {
            if(node->left->priority > node->right->priority) {
                node = right_rotate(node);
                node->right = remove(node->right, value);
            } else {
                node = left_rotate(node);
                node->left = remove(node->left, value);
            }
        }
    }
    return node;
}

template<typename T>
Node<T> *Treap<T>::right_rotate(Node<T> *y) {
    Node<T> *aux = y->left;
    y->left = aux->right;
    aux->right = y;
    return aux;
}

template<typename T>
Node<T> *Treap<T>::left_rotate(Node<T> *x) {
    Node<T> *aux = x->right;
    x->right = aux->left;
    aux->left = x;
    return aux;
}

template<typename T>
Node<T> * Treap<T>::lte_max(Node<T> *node, T value) {
    Node<T> *result = nullptr;
    while(node) {
        if(node->data <= value) {
            if(!result || node->data > result->data)
                result = node;
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return result;
}

template<typename T>
Node<T> * Treap<T>::mte_min(Node<T> *node, T value) {
    Node<T> *result = nullptr;
    while(node) {
        if(node->data >= value) {
            result = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return result;
}

template<typename T>
bool Treap<T>::find(const T &value) const {
    return find(root, value) != nullptr;
}

template<typename T>
Node<T> *Treap<T>::find(Node<T> *node, T value) {
    while(node) {
        if(value == node->data)
            return node;
        if(value < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return nullptr;
}

template<typename T>
void Treap<T>::print() const {
    print(root);
    std::cout << std::endl;
}

template<typename T>
void Treap<T>::print(Node<T> *node) const {
    if(node) {
        print(node->left);
        std::cout << node->data << " ";
        print(node->right);
    }
}

template<typename T>
void Treap<T>::print(T X, T Y) const {
    print(root, X, Y);
    std::cout << std::endl;
}

template<typename T>
Node<T> * Treap<T>::lte_max(T value) {
    return lte_max(root, value);
}

template<typename T>
Node<T> * Treap<T>::mte_min(T value) {
    return mte_min(root, value);
}

template<typename T>
void Treap<T>::print(Node<T> *node, T X, T Y) const {
    if(node) {
        if(node->data >= X) {
            print(node->left, X, Y);
        }
        if(node->data >= X && node->data <= Y) {
            std::cout << node->data << " ";
        }
        if(node->data <= Y) {
            print(node->right, X, Y);
        }
    }
}

template<typename T>
void Treap<T>::clear(Node<T> *node) {
    if(node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
