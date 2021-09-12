//
// Created by Gautam Sharma on 9/12/21.
//

#ifndef TENSORLITE_UTILITY_H
#define TENSORLITE_UTILITY_H

#include <cstdio>

enum operation {
    ADD = 0,
    SUBTRACT = 1
};


struct shape {
    size_t first_dimension;
    size_t second_dimension;

    bool operator==(const shape &rhs) const;

    bool operator!=(const shape &rhs) const;

};
#endif //TENSORLITE_UTILITY_H
