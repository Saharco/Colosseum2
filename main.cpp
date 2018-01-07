#include <iostream>
#include "AVLTree.h"
#include <cstdlib>

const int TEST_SIZE = 1000;
const int MAX_KEY = 20000;

int main() {
    AVLTree<int> *tree = new AVLTree<int>();
    int i = 0, key = 0;
    GENERATE: try {
        for (; i < TEST_SIZE; i++) {
            key = rand() % (MAX_KEY + 1);
            tree->Insert(key);
        }
    } catch(const ElementAlreadyExists& e) {
        goto GENERATE;
    }
    tree->InorderRanks();
//    tree->PreorderRanks();
    std::cout << std::endl << tree->PartialSumByOrder(5) << std::endl;
}