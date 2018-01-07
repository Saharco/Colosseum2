//
// Created by sahar on 03/01/2018.
//

#include "Colosseum.h"
#include "Exceptions.h"

Colosseum::Colosseum(int n, int *trainingGroupsIDs) {
    gladiators=NULL;
    gkc=NULL;
    groups_table=NULL;
    cmp=NULL;
    undefeated_groups=NULL;
    gladiators = new AVLTree<int>();
    try {
        GladiatorGroup **groups_arr = new GladiatorGroup *[n];
        for(int i = 0; i<n; i++) {
            groups_arr[i] = new GladiatorGroup(trainingGroupsIDs[i]);
        }
        gkc= new GladiatorKeyCalculator();
        groups_table = new HashTable<GladiatorGroup*>(gkc,groups_arr,n,3);
        cmp= new GladiatorComparator();
        undefeated_groups = new MinHeap<GladiatorGroup*>(groups_arr, n, cmp);
        delete[] (groups_arr);
        //Hash table de-allocates, heap does not.
    } catch(const std::bad_alloc& e) {
        if(!gladiators){
            delete(gladiators);
        }
        if(!gkc){
            delete(gkc);
        }
        if (!groups_table){
            delete(groups_table);
        }
        if(!cmp){
            delete(cmp);
        }
        if(!undefeated_groups){
            delete(undefeated_groups);
        }
    }
}

Colosseum::~Colosseum() {
    delete(gladiators);
    delete(undefeated_groups);
    delete(groups_table);
    delete(gkc);
    delete(cmp);
}

StatusType Colosseum::addTrainingGroup(int trainingGroupID) {
    if(trainingGroupID<0){
        return INVALID_INPUT;
    }
    try {
        GladiatorGroup* new_group = new GladiatorGroup(trainingGroupID);
        if(groups_table->member(new_group)){
            delete(new_group);
            return FAILURE;
        }
        groups_table->insert(new_group);
        undefeated_groups->insert(new_group);
    } catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup) {
    if(trainingGroup < 0 || gladiatorID < 0 || score < 0){
        return INVALID_INPUT;
    }
    GladiatorGroup dummy_group(trainingGroup);
    try{
        gladiators->Find(gladiatorID);
        if(!groups_table->member(&dummy_group)){
            return FAILURE;
        }
    }catch(const ElementDoesntExist& e){
        try {
            groups_table->findElement(&dummy_group)->InsertScore(score);
            gladiators->Insert(gladiatorID);
            return SUCCESS;
        }catch(const failureException& e) {
            return FAILURE;
        }
    }
    return FAILURE;
}

StatusType Colosseum::trainingGroupFight(int trainingGroup1,
                                         int trainingGroup2, int k1, int k2) {
    if(k1 <= 0 || k2 <= 0 || trainingGroup1<0 || trainingGroup2 < 0){
        return INVALID_INPUT;
    }
    GladiatorGroup dummy_1(trainingGroup1);
    GladiatorGroup dummy_2(trainingGroup2);
    try{
        GladiatorGroup* group_1=groups_table->findElement(&dummy_1);
        GladiatorGroup* group_2=groups_table->findElement(&dummy_2);
        if(trainingGroup1==trainingGroup2 ||group_1->getDefeatedStatus() || group_2->getDefeatedStatus()){
            return FAILURE;
        }
        int score_1=groups_table->findElement(&dummy_1)->FindBiggest(k1);
        int score_2=groups_table->findElement(&dummy_2)->FindBiggest(k2);
        if(score_1 > score_2){
            group_2->setDefeatedStatus();
        }
        else if (score_2 > score_1){
            group_1->setDefeatedStatus();
        }
        else{
            if (trainingGroup1 > trainingGroup2){
                group_1->setDefeatedStatus();
            }
            else{
                group_2->setDefeatedStatus();
            }
        }
    } catch(const failureException& e){
        return FAILURE;
    }
    while(undefeated_groups->findMin()->getDefeatedStatus()){
        undefeated_groups->deleteMin();
    }
    return SUCCESS;
}

StatusType Colosseum::getMinTrainingGroup(int *trainingGroup) {
    if(!trainingGroup){
        return INVALID_INPUT;
    }
    *trainingGroup = undefeated_groups->findMin()->getId();
    return SUCCESS;
}