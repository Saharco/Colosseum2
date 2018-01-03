//
// Created by sahar on 29/12/2017.
//

#include "GladiatorGroup.h"


GladiatorGroup::GladiatorGroup(const int id) : id(id), is_defeated(false) {
    scores = new AVLTree<int>();
}
GladiatorGroup::GladiatorGroup(const GladiatorGroup& g) : id(g.id), is_defeated(is_defeated) {
    //Tree?
}
GladiatorGroup::~GladiatorGroup() {
    delete(scores);
}

/*void GladiatorGroup::InitID(const int id) {
    this->id = id;
}*/


void GladiatorGroup::InsertScore(const int score) {
//    Might throw exception
    scores->Insert(score);
}

int GladiatorGroup::FindBiggest(int k) const {
//    Might throw exception
    return scores->SmallerSumByRank(k);
}

bool GladiatorGroup::operator==(const GladiatorGroup& g) const {
    return(this->id == g.id);
}
bool GladiatorGroup::operator!=(const GladiatorGroup& g) const {
    return(!(*this == g));
}
bool GladiatorGroup::operator>(const GladiatorGroup& g) const {
    return(this->id > g.id);
}
bool GladiatorGroup::operator<(const GladiatorGroup& g) const {
    return(this->id < g.id);
}
bool GladiatorGroup::operator>=(const GladiatorGroup& g) const {
    return(this->id >= g.id);
}
bool GladiatorGroup::operator<=(const GladiatorGroup& g) const {
    return(this->id <= g.id);
}