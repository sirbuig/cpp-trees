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
TreapNode<T> *Treap<T>::insert(TreapNode<T> *node, T value) {
    if(!node)
        return new TreapNode<T>(value);

    if(value < node->data) {
        node->left = insert(static_cast<TreapNode<T> *>(node->left), value);
        if (static_cast<TreapNode<T>*>(node->left)->priority > node->priority)
            node = right_rotate(node);
    } else {
        node->right = insert(static_cast<TreapNode<T>*>(node->right), value);
        if (static_cast<TreapNode<T>*>(node->right)->priority > node->priority)
            node = left_rotate(node);
    }
    return node;
}

template<typename T>
void Treap<T>::remove(const T &value) {
    root = remove(root, value);
}

template<typename T>
TreapNode<T> *Treap<T>::remove(TreapNode<T> *node, T value) {
    if (!node)
        return nullptr;

    if (value < node->data) {
        node->left = remove(static_cast<TreapNode<T>*>(node->left), value);
    } else if (value > node->data) {
        node->right = remove(static_cast<TreapNode<T>*>(node->right), value);
    } else {
        if (!node->left) {
            auto *temp = static_cast<TreapNode<T>*>(node->right);
            delete node;
            return temp;
        } else if (!node->right) {
            auto *temp = static_cast<TreapNode<T>*>(node->left);
            delete node;
            return temp;
        } else {
            if (static_cast<TreapNode<T>*>(node->left)->priority > static_cast<TreapNode<T>*>(node->right)->priority) {
                node = right_rotate(node);
                node->right = remove(static_cast<TreapNode<T>*>(node->right), value);
            } else {
                node = left_rotate(node);
                node->left = remove(static_cast<TreapNode<T>*>(node->left), value);
            }
        }
    }
    return node;
}

template<typename T>
TreapNode<T> *Treap<T>::right_rotate(TreapNode<T> *y) {
    auto *aux = static_cast<TreapNode<T> *>(y->left);
    y->left = aux->right;
    aux->right = y;
    return aux;
}

template<typename T>
TreapNode<T> *Treap<T>::left_rotate(TreapNode<T> *x) {
    auto *aux = static_cast<TreapNode<T> *>(x->right);
    x->right = aux->left;
    aux->left = x;
    return aux;
}

template<typename T>
TreapNode<T> *Treap<T>::lte_max(TreapNode<T> *node, T value) {
    TreapNode<T> *result = nullptr;
    while (node) {
        if (node->data <= value) {
            if (!result || node->data > result->data)
                result = node;
            node = static_cast<TreapNode<T>*>(node->right);
        } else {
            node = static_cast<TreapNode<T>*>(node->left);
        }
    }
    return result;
}

template<typename T>
TreapNode<T> *Treap<T>::mte_min(TreapNode<T> *node, T value) {
    TreapNode<T> *result = nullptr;
    while (node) {
        if (node->data >= value) {
            result = node;
            node = static_cast<TreapNode<T>*>(node->left);
        } else {
            node = static_cast<TreapNode<T>*>(node->right);
        }
    }
    return result;
}

template<typename T>
bool Treap<T>::find(const T &value) const {
    return find(root, value) != nullptr;
}

template<typename T>
TreapNode<T> *Treap<T>::find(TreapNode<T> *node, T value) {
    while (node) {
        if (value == node->data)
            return node;
        if (value < node->data)
            node = static_cast<TreapNode<T>*>(node->left);
        else
            node = static_cast<TreapNode<T>*>(node->right);
    }
    return nullptr;
}

template<typename T>
void Treap<T>::print() const {
    print(root);
    std::cout << std::endl;
}

template<typename T>
void Treap<T>::print(TreapNode<T> *node) const {
    if(node) {
        print(static_cast<TreapNode<T>*>(node->left));
        std::cout << node->data << " ";
        print(static_cast<TreapNode<T>*>(node->right));
    }
}

template<typename T>
void Treap<T>::print(T X, T Y) const {
    print(root, X, Y);
    std::cout << std::endl;
}

template<typename T>
TreapNode<T> * Treap<T>::lte_max(T value) {
    return lte_max(root, value);
}

template<typename T>
TreapNode<T> * Treap<T>::mte_min(T value) {
    return mte_min(root, value);
}

template<typename T>
void Treap<T>::print(TreapNode<T> *node, T X, T Y) const {
    if (node) {
        if (node->data >= X) {
            print(static_cast<TreapNode<T>*>(node->left), X, Y);
        }
        if (node->data >= X && node->data <= Y) {
            std::cout << node->data << " ";
        }
        if (node->data <= Y) {
            print(static_cast<TreapNode<T>*>(node->right), X, Y);
        }
    }
}

template<typename T>
void Treap<T>::clear(Node<T> *node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}