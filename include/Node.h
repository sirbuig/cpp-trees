#ifndef NODE_H
#define NODE_H

#include <random>

template<typename T>
class Node {
public:
    T data;
    Node *left;
    Node *right;

    explicit Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class TreapNode : public Node<T> {
public:
    int priority;

    explicit TreapNode(T value) : Node<T>(value), priority(rand() % 65535) {}
};

#endif //NODE_H
