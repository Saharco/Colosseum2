#include <iostream>
#include "AVLTree.h"

/*class intComparator : public Comparator<int> {
public:
    intComparator(){};
    ~intComparator(){};
    int operator()(int num1, int num2) {
        int result = num1 - num2;
        if(result < 0) return -1;
        else if(result > 0) return 1;
        return 1;
    }
};*/

int main() {
    AVLTree<int>* tree = new AVLTree<int>();
    tree->Insert(10);
    tree->Insert(5);
    tree->Insert(2);
    tree->Insert(15);
    tree->Insert(43);
    tree->Insert(12);
    tree->Insert(1);
    tree->Insert(40);
    tree->Insert(22);
    tree->Insert(27);
    tree->Insert(50);
    tree->Insert(13);
    tree->Insert(14);
    tree->Insert(20);
    tree->Insert(60);
    tree->Insert(7);
    tree->Insert(8);
    tree->PreOrder();
    std::cout << std::endl;
    tree->Remove(40);
    tree->Remove(27);
    tree->Remove(22);
    tree->Remove(5);
    tree->PreOrder();
}