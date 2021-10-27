//
// Created by Gautam Sharma on 9/16/21.
//

#ifndef TENSORLITE_TENSOR2D_H
#define TENSORLITE_TENSOR2D_H

#include "Tensor.h"

// TODO: remove inheritance

template<class T>

class Tensor2D final: public Tensor<T>{
public:
    __ONLY_FOR_TESTING__ Tensor2D()  = default;

    explicit Tensor2D(const std::vector<Tensor<T>> & input);
    explicit Tensor2D(const std::initializer_list<Tensor<T>> &input);
    explicit Tensor2D(Tensor2D<T> &input){
        // give up current ownership
        this->reset();

        // points to the input tensor
        // takes in the new ownership
        ptrToTensor2D = std::make_unique<std::vector<Tensor<T>>>(input.begin(), input.end());

        this->setRows(ptrToTensor2D->size());
        this->setCols(ptrToTensor2D->at(0).size());

//        // input gives up its current ownership
        //input.reset();

    }


    __NO_DISCARD__ const shape size() const noexcept;
    const Tensor<T> &operator[](const int &idx) const;
    virtual Tensor2D &plus(const Tensor2D &other) final;

    // inplace subtraction
    virtual Tensor2D &minus(const Tensor2D &other) final;

    // TODO:
    // inplace multiplication
    // virtual Tensor2D &multiply(const Tensor2D &other) final;

    /**
     * addition by copy
     */
    virtual Tensor2D operator+(const Tensor2D &other) final;

    /**
     * subtraction by copy
     */
    virtual Tensor2D operator-(const Tensor2D &other) final;

     /**
      * multiplication by copy
      */
    Tensor2D operator*(const Tensor2D &other);

     /**
      * multiplying by scalar
      */
    Tensor2D & multiplyByScalar(const T &scalar);

    // copy assignment
    Tensor2D &operator=(const Tensor2D &other);

    // move assignment
    Tensor2D &operator=(Tensor2D &&other) noexcept;

    Tensor2D transpose();
    virtual bool operator==(Tensor2D &rhs) const final;
    virtual bool operator!=(Tensor2D &rhs) const final;
    void reset();

    /**
     *
     * @param act activation such as SIGMOID, RELU etc
     * @return performs element wise activation
     */
    Tensor2D& activation(enum activation act);

    /**
    * Different template argument T1 since ostream is a friend and not part of the Tensor class
    */
    template<class T1>
    friend std::ostream &operator<<(std::ostream &os, Tensor2D<T1> &t1);

    void setRows(size_t rows);
    void setCols(size_t cols);

    __DO_NOT_CALL__
    std::unique_ptr<std::vector<Tensor<T>>> & getUnderlying2DPtr() ;

    __DO_NOT_CALL__
    auto begin() const noexcept -> decltype(typename std::vector<Tensor<T>>::iterator());

    __DO_NOT_CALL__
    auto end() const noexcept -> decltype(typename std::vector<Tensor<T>>::iterator());



private:
    bool isValidInput(const std::vector<Tensor<T>> &input);

    std::unique_ptr<std::vector<Tensor<T>>> ptrToTensor2D = nullptr;
    size_t rows_ = 0 ;
    size_t cols_ = 0;
};


template<class T1>
std::ostream &operator<<(std::ostream &os, Tensor2D<T1> &input) {
    auto input_shape = input.size();
    std::cout << "Tensor2D {" << std::endl;
    for (int tensor_idx = 0; tensor_idx < input_shape.first_dimension; tensor_idx++) {
        // TODO: Not efficient to make a new Tensor just to print
        Tensor<T1> temp(input[tensor_idx]);
        os << temp;
    }
    os << " }" << std::endl;
    return os;
}

#endif //TENSORLITE_TENSOR2D_H
