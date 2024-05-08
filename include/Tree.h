#ifndef TREE_H
#define TREE_H

template<typename T>
class Tree {
public:
    virtual ~Tree() = default;

    virtual void insert(const T& value) = 0;
    virtual void remove(const T& value) = 0;
    virtual bool find(const T& value) const = 0;
    virtual void print() const = 0;
    virtual void print(T X, T Y) const = 0;
};

#endif //TREE_H
