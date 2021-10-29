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
#include "math.h"


template<class T>
class Tensor{
public:

    Tensor() noexcept = default;
    explicit Tensor(const std::vector<T> & input) noexcept;
    Tensor(const std::initializer_list<T> &input) noexcept;
    Tensor(const Tensor & input) noexcept;
    Tensor(Tensor && input) noexcept;
    Tensor& operator = (Tensor && input) noexcept;
    __NO_DISCARD__ size_t size() const noexcept;



    /**
     *
     * @param idx element at index idx
     * @return const element of type T at index idx
     */
    const T& operator[] (const int &idx) const;

    /**
     * Inplace addition
     * @param other
     * @return
     */
    virtual Tensor &plus(const Tensor &other);

    /**
     * Inplace subtraction
     * @param other
     * @return
     */
    virtual Tensor &minus(const Tensor &other);

    /**
     * Inplace multiplication
     * @param other
     * @return
     */
    virtual Tensor &multiply(const Tensor &other);

    /**
     * Addition by copy
     * @param other
     * @return
     */
    virtual Tensor operator+(const Tensor &other);

    /**
     * Subtraction by copy
     * @param other
     * @return
     */
    virtual Tensor operator-(const Tensor &other);

    /**
     * Multiplication by copy
     * @param other
     * @return
     */
    Tensor operator*(const Tensor &other);

    Tensor& multiplyByScalar(const T &scalar);
    Tensor& activation(activation act );
    Tensor &operator=(const Tensor &other);
    virtual bool operator==(Tensor &rhs) const;
    virtual bool operator!=(Tensor &rhs) const;


    /**
    * Different template argument T1 since ostream is a friend and not part of the Tensor class
    */
     template<class T1>
     friend std::ostream &operator<<(std::ostream &os, Tensor<T1> &t1);

    /**
    *
    * @return unique_ptr to the underlying vector of tensors.
    * DO NOT CALL
    */
    __DO_NOT_CALL__
    std::unique_ptr<std::vector<T>> & getUnderlyingPtr();

protected:
    /**
     * CPP STL style begin iterator
     * @return begin() iterator
     */
    __DO_NOT_CALL__
    auto begin() const noexcept -> decltype(typename std::vector<T>::iterator());

    /**
    * CPP STL style end iterator
    * @return end() iterator
    */
    __DO_NOT_CALL__
    auto end() const noexcept -> decltype(typename std::vector<T>::iterator());

    /**
     *
     * @return first element of the tensor
     */
    __DO_NOT_CALL__
    virtual T front() const;

    /**
     *
     * @return last element of the tensor
     */
    __DO_NOT_CALL__
    virtual T back() const;

    virtual Tensor addOrSubtractByCopy(const Tensor &other, operation op) const;
    virtual Tensor &addOrSubtractInPlace(const Tensor &other, operation op);

    /**
     * Handy function to get the tensor copy
     * @return
     */
    virtual Tensor getTensorCopy() const;



private:

    std::vector<T> tensor_;
    std::unique_ptr<std::vector<T>> ptrToTensor = nullptr;

};

template<class T1>
std::ostream &operator<<(std::ostream &os, Tensor<T1> &input) {
    const Tensor tensorCopy = input.getTensorCopy();
    os << "{ ";
    for (size_t i = 0; i < input.size() - 1; i++) {
        os << tensorCopy[i] << ",";
    }

    os << tensorCopy[input.size() - 1] << " ";
    os << "}" << std::endl;

    return os;
}

#endif //TENSOR_H
