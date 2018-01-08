#include <iostream>
#include "AVLTree.h"
#include <cstdlib>

const int TEST_SIZE = 1000;
const int MAX_KEY = 1000;

int main() {
    AVLTree<int> *tree = new AVLTree<int>();
    int i = 0, data = 0;
    for (; i < TEST_SIZE; i++) {
        data = rand() % (MAX_KEY + 1);
        tree->Insert(data);
    }
    tree->InorderRanks();
//    tree->PreorderRanks();
    std::cout << std::endl << tree->PartialSumByOrder(5) << std::endl;
    delete (tree);
}