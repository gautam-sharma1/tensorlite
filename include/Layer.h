//
// Created by Gautam Sharma on 9/23/21.
//

#ifndef TENSORLITE_LAYER_H
#define TENSORLITE_LAYER_H

#include "Tensor2D.h"
#include "Utility.h"
#include <random>
#include "Activations.h"

template<class T>
class Layer{
public:
    Layer() = default;
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

        //Activations a;
    }


    __NO_DISCARD__ shape size() const noexcept{
        return shape({input_,output_});
    }

    const Tensor<T> &operator[](const int &idx) const{
        __ASSERT__(idx>=0);
        return tensor2D_[idx];
    }

    // inplace multiply by a scalar
    void multiply(const T & scalar){
        tensor2D_.multiplyByScalar(scalar);
    }

    // inplace multiply by a Layer
    Layer<T> multiply(const Layer &layer){
        __ASSERT__(this->output_ == layer.getInput());
        Tensor2D<T> newTensor(tensor2D_ * layer.tensor2D_);
        this->tensor2D_ = std::move(newTensor);
        this->output_ = layer.getOutput();
        return *this;
    }

    /**
     *
     * Sigmoid activation
     * S(x) = 1 / 1+e^(-x)
     * IMPORTANT : changes inplace
     * T = Tensor2D
     * @return element wise sigmoid activation
     */
    Layer<T> sigmoid(){
        //Activations::sigmoid_<Tensor2D<T>>(this->tensor2D_);
        tensor2D_.activation(activation::SIGMOID);
        return *this;
    }

    __NO_DISCARD__ size_t getInput() const{
        return this->input_;
    }

    __NO_DISCARD__ size_t getOutput() const{
        return this->output_;
    }


    template<class T1>
    friend std::ostream &operator<<(std::ostream &os, Layer<T1> &t1);

    __DO_NOT_CALL__ Tensor2D<T> tensor2D_;

private:

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
