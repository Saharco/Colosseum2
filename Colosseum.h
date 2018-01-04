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
class GladiatorComparator : public Comparator<GladiatorGroup*> {
public:
    GladiatorComparator(){};
    ~GladiatorComparator(){};
    int operator()(GladiatorGroup* g1, GladiatorGroup* g2) {
        if(g1->getDefeatedStatus()){
            return -1;
        }
        else if(g2->getDefeatedStatus()){
            return 1;
        }
        else return g1->getId()-g2->getId();
    }
};
class GladiatorKeyCalculator : public KeyCalculator<GladiatorGroup*>{
public:
    int operator()(GladiatorGroup* element) {
        return element->getId();
    };
};
class Colosseum {
    AVLTree<int>* gladiators;
    HashTable<GladiatorGroup*>* groups_table;
    MinHeap<GladiatorGroup*>* undefeated_groups;
    GladiatorKeyCalculator *gkc;
    GladiatorComparator *cmp;
public:
    Colosseum(int n, int* trainingGroupsIDs);
    ~Colosseum();
    StatusType addTrainingGroup(int trainingGroupID);
    StatusType addGladiator(int gladiatorID, int score, int trainingGroup);
    StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    StatusType getMinTrainingGroup(int* trainingGroup);
};


#endif //COLOSSEUM2_COLOSSEUM_H
