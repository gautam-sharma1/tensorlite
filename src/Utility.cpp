//
// Created by Gautam Sharma on 9/12/21.
//

#include "Utility.h"


bool shape::operator==(const shape &rhs) const {
    return first_dimension == rhs.first_dimension && second_dimension == rhs.second_dimension;
}

bool shape::operator!=(const shape &rhs) const {
    return !(shape::operator==(rhs));
}
