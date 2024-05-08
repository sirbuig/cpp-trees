#include <iostream>
#include "include/Treap.h"

int main() {
    Treap<int> t;
    t.insert(1);
    t.insert(46);
    t.insert(16);
    t.insert(1029);
    t.insert(0);
    t.print();

    t.remove(16);
    t.print();

    std::cout << (t.find(4) ? "Found\n" : "Not Found\n");
    std::cout << (t.find(1029) ? "Found\n" : "Not Found\n");

    const TreapNode<int> *result = t.lte_max(47);
    std::cout << result->data << "\n";
    result = t.mte_min(48);
    std::cout << result->data << "\n";

    return 0;
}