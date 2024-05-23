#include <iostream>
#include <fstream>
#include <chrono>
#include "include/Treap.h"
#include "include/SplayTree.h"

void testTreap(int size, std::ofstream& outputFile) {
    Treap<int> treap;
    auto start = std::chrono::steady_clock::now();

    // for insertion
    for(int i=0; i < size; i++) {
        treap.insert(rand());
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Treap - Insertion for " << size << " elements: " << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";
    outputFile << std::chrono::duration<double, std::milli>(end-start).count() << ",";

    // for deletion
    for(int i=0; i < size; i++) {
        treap.remove(rand());
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Treap - Deletion for " << size << " elements: " << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";
    outputFile << std::chrono::duration<double, std::milli>(end-start).count() << ",";

    // for find
    for(int i=0; i < size; i++) {
        treap.find(rand());
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Treap - Find for " << size << " elements: " << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";
    outputFile << std::chrono::duration<double, std::milli>(end-start).count() << ",";
}

void testSplayTree(int size, std::ofstream& outputFile) {
    SplayTree<int> splayTree;
    auto start = std::chrono::steady_clock::now();

    // for insertion
    for(int i=0; i < size; i++) {
        splayTree.insert(rand());
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "SplayTree - Insertion for " << size << " elements: " << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";
    outputFile << std::chrono::duration<double, std::milli>(end-start).count() << ",";

    // for deletion
    for(int i=0; i < size; i++) {
        splayTree.remove(rand());
    }
    end = std::chrono::steady_clock::now();
    std::cout << "SplayTree - Deletion for " << size << " elements: " << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";
    outputFile << std::chrono::duration<double, std::milli>(end-start).count() << ",";

    // for find
    for(int i=0; i < size; i++) {
        splayTree.find(rand());
    }
    end = std::chrono::steady_clock::now();
    std::cout << "SplayTree - Find for " << size << " elements: " << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";
    outputFile << std::chrono::duration<double, std::milli>(end-start).count() << ",";
}

int main() {
    int testSize = 1000000;

    std::ofstream outputFile("timing_data.csv");
    outputFile << "Insertion_Treap,Deletion_Treap,Find_Treap,Insertion_SplayTree,Deletion_SplayTree,Find_SplayTree\n";

    testTreap(testSize, outputFile);
    testSplayTree(testSize, outputFile);

    return 0;
}