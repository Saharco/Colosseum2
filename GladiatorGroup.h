//
// Created by sahar on 29/12/2017.
//

#ifndef COLOSSEUM2_GLADIATORGROUP_H
#define COLOSSEUM2_GLADIATORGROUP_H


class GladiatorGroup {
    const int id;
//    ScoresTree scores;
    bool is_defeated;
public:
    GladiatorGroup(const int id);
    GladiatorGroup(const GladiatorGroup& g);
    ~GladiatorGroup();
    bool operator==(const GladiatorGroup& g) const;
    bool operator!=(const GladiatorGroup& g) const;
    bool operator>(const GladiatorGroup& g) const;
    bool operator<(const GladiatorGroup& g) const;
    bool operator>=(const GladiatorGroup& g) const;
    bool operator<=(const GladiatorGroup& g) const;
};


#endif //COLOSSEUM2_GLADIATORGROUP_H
