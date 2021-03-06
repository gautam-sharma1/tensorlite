//
// Created by Gautam Sharma on 9/12/21.
//

#include "Tensor.h"

/*
 *
 * ******************************    Tensor class definition  *****************************************
 *
 */

template<class T>
Tensor<T>::Tensor(const std::vector<T> &input) noexcept{
    ptrToTensor = std::make_unique<std::vector<T>>(input);
}

template<class T>
Tensor<T>::Tensor(const std::initializer_list<T> &input) noexcept{
    ptrToTensor = std::make_unique<std::vector<T>>(input);
}

template<class T>
size_t Tensor<T>::size() const noexcept {
    return ptrToTensor->size();
}

template<class T>
Tensor<T> Tensor<T>::addOrSubtractByCopy(const Tensor &other, operation op) const {
    std::vector<T> dest(ptrToTensor->begin(), ptrToTensor->end());
    if (other.size() > 1) {
                __ASSERT__(other.size() == this->size());
        if (op == operation::ADD) {
            std::transform(ptrToTensor->begin(), ptrToTensor->end(), other.begin(), dest.begin(),
                           std::plus<T>());
        }

        else {
            std::transform(ptrToTensor->begin(), ptrToTensor->end(), other.begin(), dest.begin(),
                           std::minus<T>());
        }

    }
        // other is a single element tensor
    else {
                __ASSERT__(other.size() == 1);
        if (op == operation::ADD) {
            std::for_each(dest.begin(), dest.end(), [&other](T &d) { d += other.front(); });
        } else {
            std::for_each(dest.begin(), dest.end(), [&other](T &d) { d -= other.front(); });
        }
    }
    return Tensor<T>(dest);
}

template<class T>
Tensor<T> &Tensor<T>::addOrSubtractInPlace(const Tensor &other, operation op) {
    if (other.size() > 1) {
                __ASSERT__(other.size() == this->size());
        if (op == operation::ADD) {
            std::transform(ptrToTensor->begin(), ptrToTensor->end(), other.begin(), ptrToTensor->begin(),
                           std::plus<T>());
        } else {
            std::transform(ptrToTensor->begin(), ptrToTensor->end(), other.begin(), ptrToTensor->begin(),
                           std::minus<T>());
        }
    }

        // other is a single element tensor
    else {
                __ASSERT__(other.size() == 1);
        if (op == operation::ADD) {
            std::for_each(ptrToTensor->begin(), ptrToTensor->end(), [&other](T &d) { d += other.front(); });
        } else {
            std::for_each(ptrToTensor->begin(), ptrToTensor->end(), [&other](T &d) { d -= other.front(); });
        }
    }

    return (*this);
}


template<class T>
bool Tensor<T>::operator==(Tensor &rhs) const {
    return (this->size() == rhs.size() &&
            std::equal(this->begin(), this->end(), rhs.begin()));
}

template<class T>
bool Tensor<T>::operator!=(Tensor &rhs) const {
    return !(*this == rhs);
}

/*
* Returns a new vector
*/
template<class T>
Tensor<T> Tensor<T>::operator+(const Tensor &other) {
    /*
     * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
     *  broadcasting
     */
    return this->addOrSubtractByCopy(other, operation::ADD);
}

/*
* Returns a new vector
*/
template<class T>
Tensor<T> Tensor<T>::operator-(const Tensor &other) {
    /*
     * Two tensors should either be the same size or the second tensor should be a single elements tensor to allow
     *  broadcasting
     */
    return this->addOrSubtractByCopy(other, operation::SUBTRACT);
}

template<class T>

auto Tensor<T>::begin() const noexcept -> decltype(typename std::vector<T>::iterator()){
    return ptrToTensor->begin();
}

template<class T>
auto Tensor<T>::end() const noexcept -> decltype(typename std::vector<T>::iterator()){
    return ptrToTensor->end();
}

// return by copy so need to make return value const
template<class T>
T Tensor<T>::front() const {
            __ASSERT__(this->size() >= 1);
    return ptrToTensor->front();
}

// return by copy so need to make return value const
template<class T>
T Tensor<T>::back() const {
    __ASSERT__(this->size() >= 1);
    return ptrToTensor->back();
}

template<class T>
Tensor<T> Tensor<T>::getTensorCopy() const {
    std::vector<T> toReturnVector = *(this->ptrToTensor);
    return Tensor(toReturnVector);
}

template<class T>
const T& Tensor<T>::operator [](const int &idx) const {
    return this->ptrToTensor->at(idx);
}


template<class T>
Tensor<T> &Tensor<T>::plus(const Tensor &other) {
    return this->addOrSubtractInPlace(other, operation::ADD);
}

template<class T>
Tensor<T> &Tensor<T>::minus(const Tensor &other) {
    return this->addOrSubtractInPlace(other, operation::SUBTRACT);
}

template<class T>
Tensor<T> &Tensor<T>::operator=(const Tensor &other) {

    // give up current ownership
    this->ptrToTensor.reset();

    // points to a newly constructed tensor
    this->ptrToTensor = std::make_unique<std::vector<T>>(other.begin(), other.end());
    //TODO:
    // destroy other
    return *this;
}

template<class T>
Tensor<T>::Tensor(const Tensor &input) noexcept {

    // first releases current ownership if any
    this->ptrToTensor.reset();

    // takes in new ownership
    this->ptrToTensor = std::make_unique<std::vector<T>>(input.begin(), input.end());
}

template<class T>
Tensor<T>::Tensor(Tensor &&input) noexcept{

    // NOTE: The std::move function converts the lvalue other to an rvalue.
    *this = std::move(input);


}

// returning by const reference since do not want the caller to modify the value
// TODO: change this or remove this
__DO_NOT_CALL__
template<class T>
std::unique_ptr<std::vector<T>> &Tensor<T>::getUnderlyingPtr(){
    return this->ptrToTensor;
}

template<class T>
Tensor<T> &Tensor<T>:: operator=(Tensor &&input) noexcept {
    __ASSERT__(this != &input);
    // first releases current ownership if any
    this->ptrToTensor.reset();

    // moves up new data

    this->ptrToTensor = std::make_unique<std::vector<T>>(input.begin(), input.end());

    // free up input resources
    input.ptrToTensor.reset();
    input.ptrToTensor = nullptr;

    return *this;


}

template<class T>
Tensor<T> &Tensor<T>::multiply(const Tensor &other) {

    __ASSERT__(other.size() == this->size());
    std::transform(this->begin(), this->end(), other.begin(), this->begin(),
                   std::multiplies<T>());
    return *this;

}

template<class T>
Tensor<T> &Tensor<T>::multiplyByScalar(const T& scalar) {
    std::for_each(this->begin(), this->end(), [&](T &x){x *= scalar; });
    return *this;
}

template<class T>
Tensor<T> &Tensor<T>::activation(enum activation act) {
    switch(act) {
        case(activation::SIGMOID):
            std::for_each(this->begin(), this->end(), [&](T &x) { x = 1 / (1 + exp(-x)); });
        case(activation::RELU):
            std::for_each(this->begin(), this->end(), [&](T &x) {  x > 0 ? x : 0; });


    }
    return *this;
}

template class Tensor<int>;
template class Tensor<float>;
template class Tensor<double>;
template class Tensor<int_fast16_t>;
template class Tensor<int8_t>;
template class Tensor<int64_t>;

// EOF