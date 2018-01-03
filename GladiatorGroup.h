//
// Created by sahar on 29/12/2017.
//

#ifndef COLOSSEUM2_GLADIATORGROUP_H
#define COLOSSEUM2_GLADIATORGROUP_H


class GladiatorGroup {
    const int id;
    AVLTree<int>* scores;
    bool is_defeated;
public:
    GladiatorGroup(const int id);
    GladiatorGroup(const GladiatorGroup& g);
    ~GladiatorGroup();
//    void InitID(const int id);
    void InsertScore(const int score);
    int FindBiggest(int k) const;
    int getId() const;
    bool operator==(const GladiatorGroup& g) const;
    bool operator!=(const GladiatorGroup& g) const;
    bool operator>(const GladiatorGroup& g) const;
    bool operator<(const GladiatorGroup& g) const;
    bool operator>=(const GladiatorGroup& g) const;
    bool operator<=(const GladiatorGroup& g) const;
};


#endif //COLOSSEUM2_GLADIATORGROUP_H
