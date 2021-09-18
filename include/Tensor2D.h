//
// Created by Gautam Sharma on 9/16/21.
//

#ifndef TENSORLITE_TENSOR2D_H
#define TENSORLITE_TENSOR2D_H

#include "Tensor.h"


template<class T>

class Tensor2D : public Tensor<T>{
public:
    __ONLY_FOR_TESTING__ Tensor2D() noexcept = default;
    explicit Tensor2D(const std::vector<Tensor<T>> & input) noexcept;
    __NO_DISCARD__ shape size() const noexcept;
    const Tensor<T> &operator[](const int &idx) const;
    virtual Tensor2D &plus(const Tensor2D &other) final;
//
//    // inplace subtraction
    virtual Tensor2D &minus(const Tensor2D &other) final;
//
//    // inplace multiplication
//    virtual Tensor2D &multiply(const Tensor2D &other) final;
//
    // addition by copy
    virtual Tensor2D operator+(const Tensor2D &other) final;
//
//    // subtraction by copy
//    virtual Tensor2D operator-(const Tensor2D &other) final;
//
//    // multiplication by copy
//    Tensor2D operator*(const Tensor2D &other);
//
//
//
//    virtual Tensor2D &operator=(const Tensor2D &other) final;
    virtual bool operator==(Tensor2D &rhs) const final;
    virtual bool operator!=(Tensor2D &rhs) const final;
//
//
//    /*
//    * Different template argument T1 since ostream is a friend and not part of the Tensor class
//    */
//    template<class T1>
//    friend std::ostream &operator<<(std::ostream &os, Tensor2D<T1> &t1);

private:
    bool isValidInput(const std::vector<Tensor<T>> &input);
    std::unique_ptr<std::vector<Tensor<T>>> ptrToTensor2D = nullptr;
    size_t rows_ = 0 ;
    size_t cols_ = 0;
};


//template<class T1>
//std::ostream &operator<<(std::ostream &os, Tensor2D<T1> &input) {
//    const Tensor tensorCopy = input.getTensorCopy();
//    os << "Tensor{ ";
//    for (size_t i = 0; i < input.size() - 1; i++) {
//        os << tensorCopy[i] << ",";
//    }
//
//    os << tensorCopy[input.size() - 1] << " ";
//    os << "}" << std::endl;
//
//    return os;
//}


#endif //TENSORLITE_TENSOR2D_H
