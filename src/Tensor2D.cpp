//
// Created by Gautam Sharma on 9/16/21.
//

#include "Tensor2D.h"
#include <algorithm>


template<class T>
Tensor2D<T>::Tensor2D(const std::vector<Tensor<T>> &input) noexcept{

    __CHECK__(!isValidInput(input)){
        throw std::logic_error("Cannot instantiate Tensor2D with tensors of different size");
    }
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

template<class T>
const Tensor<T> &Tensor2D<T>::operator[](const int &idx) const {
    return ptrToTensor2D->at(idx);
}

template<class T>
shape Tensor2D<T>::size() const noexcept {
    return shape({this->rows_, this->cols_});
}

/*
* Modifies in place
*/
template<class T>
Tensor2D<T> &Tensor2D<T>::plus(const Tensor2D &other) {
    __ASSERT__(other.size() == this->size());
    for (auto r = 0; r < rows_; r++) {
        Tensor<T> &temp1 = ptrToTensor2D->at(r);
        Tensor<T> temp2 = other[r]; // Tensor<T>
        temp1.plus(temp2);
    }
    return *this;
}

/*
* Modifies in place
*/
template<class T>
Tensor2D<T> &Tensor2D<T>::minus(const Tensor2D &other) {
    __ASSERT__(other.size() == this->size());
    for (auto r = 0; r < rows_; r++) {
        Tensor<T> &temp1 = ptrToTensor2D->at(r);
        Tensor<T> temp2 = other[r]; // Tensor<T>
        temp1.minus(temp2);
    }
    return *this;
}

/*
* Modifies by copy
*/
template<class T>
Tensor2D<T> Tensor2D<T>::operator+(const Tensor2D &other) {
    std::vector<Tensor<T>> toReturn;
    __ASSERT__(other.size() == this->size());
    for (auto r = 0; r < rows_; r++) {
        Tensor<T> temp1 = ptrToTensor2D->at(r);
        Tensor<T> temp2 = other[r]; // rth Tensor<T>
        Tensor<T> temp_result = temp1 + temp2;
        toReturn.push_back(temp_result);
    }

    return Tensor2D<T>(toReturn);
}

template<class T>
bool Tensor2D<T>::operator==(Tensor2D &rhs) const {
       for (auto r = 0; r < rows_; r++) {
        Tensor<T> first = ptrToTensor2D->at(r);
        Tensor<T> second = rhs[r];
        if (first != second) {
            return false;
        }
    }
    return true;
}

template<class T>
bool Tensor2D<T>::operator!=(Tensor2D &rhs) const {
    return !(*this == rhs);
}



// explicit class initialization
template class Tensor2D<int>;
template class Tensor2D<float>;
template class Tensor2D<double>;
template class Tensor2D<int_fast16_t>;
template class Tensor2D<int8_t>;
template class Tensor2D<int64_t>;