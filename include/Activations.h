//
// Created by Gautam Sharma on 10/26/21.
//

#ifndef TENSORLITE_ACTIVATIONS_H
#define TENSORLITE_ACTIVATIONS_H


#include <math.h>
#include "Utility.h"

namespace Activations{



    template<class T>
    T sigmoid_(T &input){
        return input.activation(activation::SIGMOID);
    }
};






#endif //TENSORLITE_ACTIVATIONS_H