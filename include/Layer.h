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
    Layer(size_t in = 10, size_t out = 10, T mean = 0, T stddev = 1):input_(in), output_(out){
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::normal_distribution<> distrib(mean, stddev);
        std::vector<Tensor<T>> result;
        for(int i=0; i<input_; i++){
            std::vector<T> row;
            for(int j=0; j<output_; j++){
                row.push_back(distrib(gen));
            }
            result.push_back(Tensor<T>(row));
        }
            tensor2D_ = Tensor2D<T>(result);
    }

    __NO_DISCARD__ const shape size() const noexcept{
        return shape({input_,output_});
    }

    const Tensor<T> &operator[](const int &idx) const{
        __ASSERT__(idx>=0);
        return tensor2D_[idx];
    }

    template<class T1>
    friend std::ostream &operator<<(std::ostream &os, Layer<T1> &t1);



private:
    Tensor2D<T> tensor2D_;
    size_t input_;
    size_t output_;
};

template<class T1>
std::ostream &operator<<(std::ostream &os, Layer<T1> &input) {
    auto input_shape = input.size();
    std::cout << "Layer {" << std::endl;
    for (int tensor_idx = 0; tensor_idx < input_shape.first_dimension; tensor_idx++) {
        Tensor<T1> temp(input[tensor_idx]);
        os << temp;
    }
    os << " }" << std::endl;
    return os;
}
#endif //TENSORLITE_LAYER_H
