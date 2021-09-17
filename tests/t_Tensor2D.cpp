//
// Created by Gautam Sharma on 9/16/21.
//

#include <iostream>
#include <gtest/gtest.h>
#include "Tensor2D.h"

TEST(GTtest, CanInitializeDefaultTensor2D){
Tensor2D<int> t;
}

TEST(GTtest, CanInitializeTensor2D){
    Tensor<float> t1 = {1,2,3,4};
    Tensor<float> t2 = {1,2,3,4};
    Tensor<float> t3 = {1,2,3,4};
    std::vector<Tensor<float>> input = {t1,t2,t3};
    Tensor2D<float> t(input);
}

