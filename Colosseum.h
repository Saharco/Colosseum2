//
// Created by sahar on 03/01/2018.
//

#ifndef COLOSSEUM2_COLOSSEUM_H
#define COLOSSEUM2_COLOSSEUM_H

#include "library2.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "MinHeap.h"
#include "GladiatorGroup.h"
class intComparator : public Comparator<int> {
public:
    intComparator(){};
    ~intComparator(){};
    int operator()(int num1, int num2) {
        int result = num1 - num2;
        if(result < 0) return -1;
        else if(result > 0) return 1;
        return 1;
    }
};
class GladiatorKeyCalculator : public KeyCalculator<GladiatorGroup*>{
public:
    int operator()(const GladiatorGroup* &element){
        return element->getId();
    };
};
class Colosseum {
    AVLTree<int>* gladiators;
    HashTable<GladiatorGroup*>* groups_table;
    MinHeap<GladiatorGroup*>* undefeated_groups;
    GladiatorKeyCalculator *gkc;
    intComparator *cmp;
public:
    Colosseum(int n, int* trainingGroupsIDs);
    ~Colosseum();
    StatusType addTrainingGroup(int trainingGroupID);
    StatusType addGladiator(int gladiatorID, int score, int trainingGroup);
    StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    StatusType getMinTrainingGroup(int* trainingGroup);
};


#endif //COLOSSEUM2_COLOSSEUM_H
