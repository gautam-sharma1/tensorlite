////
//// Created by Gautam Sharma on 10/26/21.
////
//
//#include "Activations.h"
//
///**
// * Sigmoid activation
// * S(x) = 1 / 1+e^(-x)
// * IMPORTANT : changes inplace
// */
//template<class T>
//Layer<T>& Activations::sigmoid_(Layer<T> &input){
//    auto input_shape = input.size();
//    for (int tensor_idx = 0; tensor_idx < input_shape.first_dimension; tensor_idx++) {
//        for (int tensor_jdx = 0; tensor_jdx < input_shape.second_dimension; tensor_jdx++) {
//            input[tensor_idx][tensor_jdx] = 1/ (1 + exp(-input[tensor_idx][tensor_jdx]));
//        }
//    }
//    return input;
//}
//
//
//
//
//template class Tensor<int>;
//template class Tensor<float>;
//template class Tensor<double>;
//template class Tensor<int_fast16_t>;
//template class Tensor<int8_t>;
//template class Tensor<int64_t>;