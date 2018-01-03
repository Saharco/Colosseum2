//
// Created by sahar on 03/01/2018.
//

#include "library2.h"
#include "Colosseum.h"

void *init(int n, int *trainingGroupIDs) {
    Colosseum *DS = new Colosseum(n, trainingGroupIDs);
    return (void *) DS;
}

StatusType addTrainingGroup(void *DS, int trainingGroupID) {
    return ((Colosseum *) DS)->addTrainingGroup(trainingGroupID);
}

StatusType addGladiator(void *DS, int gladiatorID, int score, int
trainingGroup) {
    return ((Colosseum *) DS)->addGladiator(gladiatorID, score, trainingGroup);
}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int
trainingGroup2, int k1, int k2) {
    return ((Colosseum *) DS)->trainingGroupFight(trainingGroup1,
                                                  trainingGroup2, k1, k2);
}

StatusType getMinTrainingGroup(void *DS, int *trainingGroup) {
    return ((Colosseum *) DS)->getMinTrainingGroup(trainingGroup);
}

void quit(void **DS) {
    delete ((Colosseum *) *DS);
    *DS = NULL;
}