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

class Colosseum {
    AVLTree<int>* gladiators;
    HashTable<GladiatorGroup*>* groups_table;
    MinHeap<GladiatorGroup*>* undefeated_groups;

public:
    Colosseum(int n, int* trainingGroupsIDs);
    ~Colosseum();
    StatusType addTrainingGroup(int trainingGroupID);
    StatusType addGladiator(int gladiatorID, int score, int trainingGroup);
    StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    StatusType getMinTrainingGroup(int* trainingGroup);
};


#endif //COLOSSEUM2_COLOSSEUM_H
