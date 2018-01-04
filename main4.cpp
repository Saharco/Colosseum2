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
    for(int i =0; i<15; i++) {
        tree2->Insert(B[i]);
        /*std::cout << std::endl << "-------"  << std::endl;
        tree2->PreorderRanks();*/
    }
     //15 elements
    tree1->PreorderRanks();
    std::cout << std::endl << "-------"  << std::endl;
    tree2->PreorderRanks();

    /*AVLTree<int> *tree3 = new AVLTree<int>();
    tree3->Insert(2);
    tree3->Insert(10);
    tree3->Insert(20);
    tree3->PreorderRanks();*/
    /*tree->SmallerSumByRank(1); //200
    tree->SmallerSumByRank(15); //1458
    tree->SmallerSumByRank(2); //380
    tree->SmallerSumByRank(5); //800*/
}