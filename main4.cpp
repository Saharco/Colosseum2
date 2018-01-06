//
// Created by sahar on 04/01/2018.
//
#include "AVLTree.h"

//--------[30, 40, 45, 50, 60, 70, 80, 90, 95, 98, 100, 150, 170, 180, 200] (Sum is 1458)

int main() {
    AVLTree<int> *tree1 = new AVLTree<int>();
    AVLTree<int> *tree2 = new AVLTree<int>();
    int A[15] = {50,100,200,180,150,30,70,40,95,60,98,170,90,45,80};
    int B[15] = {30,40,45,50,60,70,80,90,95,98,100,150,170,180,200};
    for(int i = 0; i<15; i++)
        tree1->Insert(A[i]);
    for(int i = 0; i<15; i++) {
        tree2->Insert(B[i]);
        /*std::cout << std::endl << "-------"  << std::endl;
        tree2->PreorderRanks();*/
    }
     //15 elements
    tree1->PreorderRanks();
    std::cout << std::endl << "-------"  << std::endl;
    tree2->PreorderRanks();

    std::cout << tree2->PartialSumByOrder(1) << std::endl; //200
    std::cout << tree2->PartialSumByOrder(15) << std::endl; //1458
    std::cout << tree2->PartialSumByOrder(2) << std::endl; //380
    std::cout << tree2->PartialSumByOrder(14) << std::endl; //1428
    std::cout << tree2->PartialSumByOrder(5) << std::endl; //800

    std::cout << tree1->PartialSumByOrder(1) << std::endl; //200
    std::cout << tree1->PartialSumByOrder(15) << std::endl; //1458
    std::cout << tree1->PartialSumByOrder(2) << std::endl; //380
    std::cout << tree2->PartialSumByOrder(14) << std::endl; //1428
    std::cout << tree1->PartialSumByOrder(5) << std::endl; //800
    std::cout << std::endl << "-------"  << std::endl;
    try {
        tree1->Insert(180);
    } catch(...) {
        tree1->PreorderRanks();
        std::cout << std::endl << "-------"  << std::endl;
    }
    try {
        tree1->Insert(150);
    } catch(...) {
        tree1->PreorderRanks();
        std::cout << std::endl << "-------"  << std::endl;
    }
    try {
        tree1->Insert(50);
    } catch(...) {
        tree1->PreorderRanks();
        std::cout << std::endl << "-------"  << std::endl;
    }
    try {
        tree1->Remove(195);
    } catch(...) {
        tree1->PreorderRanks();
        std::cout << std::endl << "-------"  << std::endl;
    }
}