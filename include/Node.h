#ifndef NODE_H
#define NODE_H

#include <random>

template<typename T>
class Node {
public:
    T data;
    int priority;
    Node *left;
    Node *right;

    explicit Node(T value) : data(value), priority(rand() % 65535),left(nullptr), right(nullptr) {}
};

#endif //NODE_H
