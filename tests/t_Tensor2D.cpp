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
// TODO
//TEST(GTtest, CanTestValidity){
//    Tensor<float> t1 = {1,2,3,4};
//    Tensor<float> t2 = {1,2,3};
//    Tensor<float> t3 = {1,2,3,4};
//    std::vector<Tensor<float>> input({t1,t2,t3});
//
//    try {
//        Tensor2D<float> t(input);
//        //FAIL() << "Expected std::out_of_range";
//    }
//    catch(std::logic_error const & err) {
//        EXPECT_EQ(err.what(),std::string("Cannot instantiate Tensor2D with tensors of different size"));
//    }
//
//}

TEST(GTtest, OverloadSquareBracketOperatorTensor2D){
    Tensor<float> t1 ({-11.10,2.555,-6.667,7,89.99});
    Tensor<float> t2({11.333,222222222.56,32232326.78,9445555.89,-51111111111.43});

    Tensor2D<float> t3 (   {t1,t2} );
    Tensor<float> EXPECTED_SECOND_TENSOR  = t3[1];
    //assert(EXPECTED_SECOND_TENSOR==t2);
    ASSERT_TRUE(EXPECTED_SECOND_TENSOR==t2);
}

TEST(GTtest, CanReturnCorrectTensorSize){
    Tensor<float> t1 ({1,2.555,6.667,7,8});
    Tensor<float> t2({1,2,3,4,5});
    Tensor<float> t3({1,2,3,4,5});
    Tensor2D<float> t4 (   {t1,t2,t3} );
    shape EXPECTED_SIZE = shape({3,5});
    shape ACTUAL_SIZE = t4.size();
    ASSERT_EQ(EXPECTED_SIZE, ACTUAL_SIZE);
}

TEST(GTtest, CanAddCorrectlyInPlaceTensor2D){
    Tensor<float> t1 ({1,2,3});
    Tensor<float> t2({3,4,5});

    /*
     * t4 = t5 =
     * {1,2,3}
     * {3,4,5}
     */
    Tensor2D<float> t4 (   {t1,t2} );
    Tensor2D<float> t5 (   {t1,t2} );


    /*
     * t4+t5 =
     * {2,4,6}
     * {6,8,10}
     */
    auto EXPECTED_TENSOR2D = t4+t5;
    t4.plus(t5);
    ASSERT_TRUE(EXPECTED_TENSOR2D==t4);

}