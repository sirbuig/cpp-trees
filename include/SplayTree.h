#ifndef TREES_SPLAYTREE_H
#define TREES_SPLAYTREE_H

#include "Tree.h"
#include "Node.h"

template<typename T>
class SplayTree final : public Tree<T> {
private:
    Node<T> *root;
    int size;

    Node<T>* findNode(const T& value) const;
    void splay(Node<T>* node);
    void rotateRight(Node<T>* node);
    void rotateLeft(Node<T>* node);
    Node<T>* maximum(Node<T>* node);
    Node<T>* minimum(Node<T>* node);
    Node<T>* successor(Node<T>* node);
    Node<T>* predecessor(Node<T>* node);
    void printInOrder(Node<T>* node) const;
    void printInRange(Node<T>* node, T X, T Y) const;
    void clear(Node<T> *node);

    Node<T>* lte_max(Node<T>* node, const T& value);
    Node<T>* mte_min(Node<T>* node, const T& value);

public:
    SplayTree();
    ~SplayTree() override;

    void insert(const T& value) override;
    void remove(const T& value) override;
    bool find(const T& value) const override;
    void print() const override;
    void print(T X, T Y) const override;
    T findPredecessor(const T& value);
    T findSuccessor(const T& value);

    Node<T>* lte_max(const T& value);
    Node<T>* mte_min(const T& value);
};

#include "../src/SplayTree.tpp"

#endif //TREES_SPLAYTREE_H
