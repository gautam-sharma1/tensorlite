//
// Created by Gautam Sharma on 9/16/21.
//

#include "Tensor2D.h"
#include <algorithm>


template<class T>
Tensor2D<T>::Tensor2D(const std::vector<Tensor<T>> &input){

    __CHECK__(!isValidInput(input)){
        throw std::logic_error("Cannot instantiate Tensor2D with tensors of different size");
    }
    ptrToTensor2D = std::make_unique<std::vector<Tensor<T>>>(input);
    std::copy(input.begin(), input.end(), (ptrToTensor2D.get())->begin());

    this->rows_ = ptrToTensor2D->size();
    this->cols_ = ptrToTensor2D->at(0).size();
}


template<class T>
Tensor2D<T>::Tensor2D(const std::initializer_list<Tensor<T>> &input){
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
const shape Tensor2D<T>::size() const noexcept {
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


/*
* Modifies by copy
*/
template<class T>
Tensor2D<T> Tensor2D<T>::operator-(const Tensor2D &other) {
    std::vector<Tensor<T>> toReturn;
            __ASSERT__(other.size() == this->size());
    for (auto r = 0; r < rows_; r++) {
        Tensor<T> temp1 = ptrToTensor2D->at(r);
        Tensor<T> temp2 = other[r]; // rth Tensor<T>
        Tensor<T> temp_result = temp1 - temp2;
        toReturn.push_back(temp_result);
    }

    return Tensor2D<T>(toReturn);
}


template<class T>
bool Tensor2D<T>::operator==(Tensor2D &rhs) const {
       for (auto r = 0; r < rows_; r++) {
        const Tensor<T> &first = ptrToTensor2D->at(r);
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

// TODO
template<class T>
Tensor2D<T> Tensor2D<T>::transpose() {
    __CHECK__(!isValidInput(*ptrToTensor2D)){
        throw std::logic_error("Cannot instantiate Tensor2D with tensors of different size");
    }
    std::vector<Tensor<T>> result;
    for (int col = 0; col < this->cols_; col++) {
        std::vector<T> currColumn;
        for (int row = 0; row < this->rows_; row++) {
            currColumn.push_back((*ptrToTensor2D)[row][col]);
        }
        result.push_back(Tensor<T>(currColumn));
    }

    return Tensor2D<T>(std::move(result));
}

/*
* Returns a new 2D Tensor
*
*/
// TODO
template<class T>
Tensor2D<T> Tensor2D<T>::operator*(const Tensor2D<T> &other) {

    __ASSERT__(other.size().first_dimension == this->size().second_dimension);
    shape rhsTensorSize = other.size();
    std::vector<Tensor<T>> result; //(this->size().first_dimension);
    result.reserve(this->size().first_dimension);
    // Matrix multiplication
    // O(n^3)
    // Can improve it using some sophisticated algorithms but leaving it for now
    for (int i = 0; i < this->rows_; i++) {
        std::vector<T> currRowToBeFilled(rhsTensorSize.second_dimension, 0);
        for (int j = 0; j < rhsTensorSize.second_dimension ; j++) {
            T temp = 0;
            for (int k = 0; k < rhsTensorSize.first_dimension; k++) {
                temp += (*ptrToTensor2D)[i][k] * other[k][j];
            }

            currRowToBeFilled[j] = temp;
        }
        result.push_back(Tensor<T>(currRowToBeFilled)); // casts vector to a tensor
    }

    return Tensor2D<T>(std::move(result));

}

template<class T>
Tensor2D<T> &Tensor2D<T>::operator=(const Tensor2D &other) {

    __ASSERT__(this != &other);

    // give up current ownership
    this->reset();

    // points to the input tensor
    // takes in the new ownership
    ptrToTensor2D = std::make_unique<std::vector<Tensor<T>>>(other.begin(), other.end());

    this->setRows(ptrToTensor2D->size());
    this->setCols(ptrToTensor2D->at(0).size());


    return *this;

}

template<class T>
Tensor2D<T> &Tensor2D<T>::operator=(Tensor2D &&other) noexcept {

    __ASSERT__(this != &other);

    // give up current ownership
    this->reset();

    // points to the input tensor
    // takes in the new ownership
    ptrToTensor2D = std::make_unique<std::vector<Tensor<T>>>(other.begin(), other.end());

    this->setRows(ptrToTensor2D->size());
    this->setCols(ptrToTensor2D->at(0).size());

    // input gives up its current ownership
    other.reset();

    return *this;

}

template<class T>
std::unique_ptr<std::vector<Tensor<T>>> &Tensor2D<T>::getUnderlying2DPtr(){
    return ptrToTensor2D;
}

template<class T>
void Tensor2D<T>::reset() {
    ptrToTensor2D.reset();
}

template<class T>
auto Tensor2D<T>::begin() const noexcept -> decltype(typename std::vector<Tensor<T>>::iterator()){
    return ptrToTensor2D->begin();
}

template<class T>
auto Tensor2D<T>::end() const noexcept -> decltype(typename std::vector<Tensor<T>>::iterator()){
    return ptrToTensor2D->end();
}

template<class T>
void Tensor2D<T>::setRows(size_t rows) {
    this->rows_ = rows;
}

template<class T>
void Tensor2D<T>::setCols(size_t cols) {
    this->cols_ = cols;
}

template<class T>
Tensor2D<T> & Tensor2D<T>::multiplyByScalar(const T &scalar){
    for (int i = 0; i < this->rows_; i++) {
        Tensor<T> & currRow = *(this->begin() + i);
        currRow.multiplyByScalar(scalar);
    }
    return *this;
}

template<class T>
Tensor2D<T> &Tensor2D<T>::activation(enum activation act) {
        for (int i = 0; i < this->rows_; i++) {
            Tensor<T> &currRow = *(this->begin() + i);
            currRow.activation(act);
        }
    return *this;
}

// in place multiplication is not needed
//template<class T>
//Tensor2D<T> &Tensor2D<T>::multiply(const Tensor2D &other) {
//    __ASSERT__(other.size().first_dimension == this->size().second_dimension);
//    // Matrix multiplication
//    // O(n^3)
//    // Can improve it using some sophisticated algorithms but leaving it for now
//    for (int i = 0; i < this->rows_; i++) {
//        ptrToTensor2D->at(i).multiply(other[i]);
//    }
//    return *this;
//}


// explicit class initialization
template class Tensor2D<int>;
template class Tensor2D<float>;
template class Tensor2D<double>;
template class Tensor2D<int_fast16_t>;
template class Tensor2D<int8_t>;
template class Tensor2D<int64_t>;