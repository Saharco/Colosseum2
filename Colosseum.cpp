//
// Created by sahar on 03/01/2018.
//

#include "Colosseum.h"

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

Colosseum::Colosseum(int n, int *trainingGroupsIDs) {
    try {
        gladiators = new AVLTree<int>();
        GladiatorGroup** groups_arr = new GladiatorGroup*[n];
        for(int i = 0; i<n; i++) {
            groups_arr[i] = new GladiatorGroup(trainingGroupsIDs[i]);
        }
        groups_table->//CONSTRUCTOR WITH AN ARRAY (DOESN'T ALLOCATE)!!!!!!!!
        ;
        intComparator cmp;
        undefeated_groups = new MinHeap<GladiatorGroup*>(groups_arr, n, cmp);
        //Hash table de-allocates, heap does not.
    } catch(...) {
        *this = NULL;
    }
}

Colosseum::~Colosseum() {

}

StatusType Colosseum::addTrainingGroup(int trainingGroupID) {
    try {

    } catch (...) {

    }
}

StatusType
Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup) {

}

StatusType Colosseum::trainingGroupFight(int trainingGroup1,
                                         int trainingGroup2, int k1, int k2) {

}

StatusType Colosseum::getMinTrainingGroup(int *trainingGroup) {

}