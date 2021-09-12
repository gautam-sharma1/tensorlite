//
// Created by Gautam Sharma on 9/12/21.
//

#ifndef UNTITLED_TENSOR_H
#define UNTITLED_TENSOR_H
#include <vector>
#include <iostream>
#include <memory>
#include <initializer_list>
#include "Directives.h"
#include "Utility.h"


template<class T>
class Tensor{
public:

    __ONLY_FOR_TESTING__ Tensor() noexcept = default;
    Tensor(const std::vector<T> & input) noexcept;
    Tensor(const std::initializer_list<T> &input) noexcept;
    Tensor(const Tensor & input) noexcept;
    __NO_DISCARD__ size_t size() const noexcept;

     /*
     * returns element at index idx
     */
    const T &operator[](int idx) const;


    // inplace subtraction
    Tensor &plus(const Tensor &other);

    // inplace addition
    Tensor &minus(const Tensor &other);

    // addition by copy
    Tensor operator+(const Tensor &other);

    // subtraction by copy
    Tensor operator-(const Tensor &other);

    Tensor &operator=(const Tensor &other);
    inline bool operator==(Tensor &rhs) const;
    inline bool operator!=(Tensor &rhs) const;


    /*
    * Different template argument T1 since ostream is a friend and not part of the Tensor class
    */
     template<class T1>
     friend std::ostream &operator<<(std::ostream &os, Tensor<T1> &t1);

protected:
    __DO_NOT_CALL__
    auto begin() const;

    __DO_NOT_CALL__
    auto end() const;

    __DO_NOT_CALL__
    auto front() const;

    __DO_NOT_CALL__
    auto back() const;

    Tensor addOrSubtractByCopy(const Tensor &other, operation op) const;
    Tensor &addOrSubtractInPlace(const Tensor &other, operation op);
    Tensor getTensorCopy() const;

private:
    std::unique_ptr<std::vector<T>> ptrToTensor;
    std::vector<T> tensor_;

};




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


template<class T1>
std::ostream &operator<<(std::ostream &os, Tensor<T1> &input) {
    const Tensor tensorCopy = input.getTensorCopy();
    os << "Tensor{ ";
    for (size_t i = 0; i < input.size() - 1; i++) {
        os << tensorCopy[i] << ",";
    }

    os << tensorCopy[input.size() - 1] << " ";
    os << "}" << std::endl;

    return os;
}

template<class T>
bool Tensor<T>::operator==(Tensor &rhs) const {
    return (this->size() == rhs.size() &&
            std::equal(this->begin(), this->end(), rhs.begin()));
}

template<class T>
bool Tensor<T>::operator!=(Tensor &rhs) const {
    return *this != rhs;
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
auto Tensor<T>::begin() const {
    return ptrToTensor->begin();
}

template<class T>
auto Tensor<T>::end() const {
    return ptrToTensor->end();
}

template<class T>
auto Tensor<T>::front() const {
    __ASSERT__(this->size() >= 1);
    return ptrToTensor->front();
}

template<class T>
auto Tensor<T>::back() const{
    __ASSERT__(this->size() >= 1);
    return ptrToTensor->back();
}

template<class T>
Tensor<T> Tensor<T>::getTensorCopy() const {
    std::vector<T> toReturnVector = *(this->ptrToTensor);
    return Tensor(toReturnVector);
}

template<class T>
const T &Tensor<T>::operator[](int idx) const {
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
    // points to a newly constructed tensor
    this->ptrToTensor = std::make_unique<std::vector<T>>(other.begin(), other.end());
    return *this;
}

template<class T>
Tensor<T>::Tensor(const Tensor &input) noexcept {

    // first releases current ownership if any
    this->ptrToTensor.release();

    // takes in new ownership
    this->ptrToTensor = std::make_unique<std::vector<T>>(input.begin(), input.end());
}

#endif //UNTITLED_TENSOR_H
