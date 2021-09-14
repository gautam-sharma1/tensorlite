//
// Created by Gautam Sharma on 9/12/21.
//

#ifndef TENSOR_H
#define TENSOR_H
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
    explicit Tensor(const std::vector<T> & input) noexcept;
    Tensor(const std::initializer_list<T> &input) noexcept;
    Tensor(const Tensor & input) noexcept;
    Tensor(Tensor && input) noexcept;
    Tensor& operator = (Tensor && input) noexcept;
    ~Tensor() = default;
    __NO_DISCARD__ size_t size() const noexcept;


    // returns element at index idx
    const T &operator[](const int &idx) const;

    // inplace subtraction
    Tensor &plus(const Tensor &other);

    // inplace addition
    Tensor &minus(const Tensor &other);

    // inplace multiplication
    Tensor &multiply(const Tensor &other);

    // addition by copy
    Tensor operator+(const Tensor &other);

    // subtraction by copy
    Tensor operator-(const Tensor &other);

    // multiplication by copy
    Tensor operator*(const Tensor &other);



    Tensor &operator=(const Tensor &other);
    inline bool operator==(Tensor &rhs) const;
    inline bool operator!=(Tensor &rhs) const;


    /*
    * Different template argument T1 since ostream is a friend and not part of the Tensor class
    */
     template<class T1>
     friend std::ostream &operator<<(std::ostream &os, Tensor<T1> &t1);

    __DO_NOT_CALL__
    std::unique_ptr<std::vector<T>> & getUnderlyingPtr();

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

    std::vector<T> tensor_;
    std::unique_ptr<std::vector<T>> ptrToTensor = nullptr;

};

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

#endif //TENSOR_H
