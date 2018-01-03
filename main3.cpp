#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree<int>* tree = new AVLTree<int>();
    tree->Insert(1024);
    tree->Insert(512);
    tree->Insert(2048);
    tree->Insert(256);
    tree->Insert(800);
    tree->Insert(1500);
    tree->Insert(2500);
    tree->Insert(128);
    tree->Insert(700);
    tree->Insert(900);
    tree->Insert(1250);
    tree->Insert(1750);
    tree->Insert(3000);
    tree->Insert(850);
    tree->Insert(950);
    tree->PreorderRanks();
    std::cout << std::endl << std::endl;
    tree->Insert(100);
    tree->Insert(50);
    tree->Insert(200);
    tree->Insert(190);
    tree->Insert(25);
    tree->Insert(10);
    tree->Insert(3500);
    tree->Insert(4000);
    try {
        tree->Insert(950);

    } catch (...) {
    }
    tree->PreorderRanks();
}