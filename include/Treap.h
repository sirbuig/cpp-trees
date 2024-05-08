#ifndef TREAP_H
#define TREAP_H

#include "Tree.h"
#include "Node.h"

template<typename T>
class Treap final : public Tree<T> {
    Node<T> *root;
    Node<T> *insert(Node<T> *node, T value);
    Node<T> *remove(Node<T> *node, T value);
    Node<T> *right_rotate(Node<T> *y);
    Node<T> *left_rotate(Node<T> *x);
    Node<T> *lte_max(Node<T> *node, T value);
    Node<T> *mte_min(Node<T> *node, T value);

    static Node<T> *find(Node<T> *node, T value);
    void print(Node<T> *node) const;
    void print(Node<T> *node, T X, T Y) const;
    void clear(Node<T> *node);

public:
    Treap();
    ~Treap() override;

    void insert(const T &value) override;
    void remove(const T &value) override;
    bool find(const T &value) const override;
    void print() const override;
    void print(T X, T Y) const override;
    Node<T> *lte_max(T value);
    Node<T> *mte_min(T value);
};

#include "../src/Treap.tpp"

#endif //TREAP_H
