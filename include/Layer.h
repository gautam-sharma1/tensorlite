//
// Created by Gautam Sharma on 9/23/21.
//

#ifndef TENSORLITE_LAYER_H
#define TENSORLITE_LAYER_H

#include "Tensor2D.h"
#include "Utility.h"
#include <random>

template<class T>
class Layer{
public:
    Layer(size_t in, size_t out):input_(in), output_(out){
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(-1, 1);
        std::vector<Tensor<T>> result;
        for(int i=0; i<input_; i++){
            std::vector<T> row;
            for(int j=0; j<output_; j++){
                row.push_back(distrib(gen));
            }
            result.push_back(Tensor<T>(row));
        }
//        Tensor2D<T> temp(result);
//        tensor2D_ = temp;
            tensor2D_ = Tensor2D<T>(result);
    }

private:
    Tensor2D<T> tensor2D_;
    size_t input_;
    size_t output_;
};


#endif //TENSORLITE_LAYER_H
