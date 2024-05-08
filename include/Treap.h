#ifndef TREAP_H
#define TREAP_H

#include "Tree.h"
#include "Node.h"

template<typename T>
class Treap final : public Tree<T> {
    TreapNode<T> *root;
    TreapNode<T> *insert(TreapNode<T> *node, T value);
    TreapNode<T> *remove(TreapNode<T> *node, T value);
    TreapNode<T> *right_rotate(TreapNode<T> *y);
    TreapNode<T> *left_rotate(TreapNode<T> *x);
    TreapNode<T> *lte_max(TreapNode<T> *node, T value);
    TreapNode<T> *mte_min(TreapNode<T> *node, T value);

    static TreapNode<T> *find(TreapNode<T> *node, T value);
    void print(TreapNode<T> *node) const;
    void print(TreapNode<T> *node, T X, T Y) const;
    void clear(Node<T> *node);

public:
    Treap();
    ~Treap() override;

    void insert(const T &value) override;
    void remove(const T &value) override;
    bool find(const T &value) const override;
    void print() const override;
    void print(T X, T Y) const override;
    TreapNode<T> *lte_max(T value);
    TreapNode<T> *mte_min(T value);
};

#include "../src/Treap.tpp"

#endif //TREAP_H
