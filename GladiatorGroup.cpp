//
// Created by sahar on 29/12/2017.
//

#include "GladiatorGroup.h"


GladiatorGroup::GladiatorGroup(const int id) : id(id) {
    //create tree!
}
GladiatorGroup::GladiatorGroup(const GladiatorGroup& g) : id(g.id) {

} //maybe delete this
GladiatorGroup::~GladiatorGroup() {
    //delete tree!
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