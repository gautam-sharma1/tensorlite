//
// Created by Gautam Sharma on 9/16/21.
//

#include "Tensor2D.h"
#include <algorithm>


template<class T>
Tensor2D<T>::Tensor2D(const std::vector<Tensor<T>> &input) noexcept{

    ptrToTensor2D = std::make_unique<std::vector<Tensor<T>>>(input);
    std::copy(input.begin(), input.end(), (ptrToTensor2D.get())->begin());

    this->rows_ = ptrToTensor2D->size();
    this->cols_ = ptrToTensor2D->at(0).size();
}

template<class T>
bool Tensor2D<T>::isValidInput(const std::vector<Tensor<T>> &input) {
    if(input.empty()){
        std::cerr << "Cannot Instantiate a Tensor2D with an empty input!" << std::endl;
        return false;
    }
    size_t kNumColumns = input[0].size();
    if (std::all_of(input.cbegin(), input.cend(), [kNumColumns](const Tensor<T> &t){ return t.size() == kNumColumns; })) {
        return true;
    }
    else{
        return false;
    }
}


template class Tensor2D<int>;
template class Tensor2D<float>;
template class Tensor2D<double>;
template class Tensor2D<int_fast16_t>;
template class Tensor2D<int8_t>;
template class Tensor2D<int64_t>;