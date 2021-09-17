//
// Created by Gautam Sharma on 9/12/21.
//

#include <iostream>
#include <gtest/gtest.h>
#include "Tensor.h"



TEST(GTtest, CanInitializeInt){
    Tensor<int8_t> t1({1,2,3,4,5});
    Tensor<int16_t> t2({1,2,3,4,5});
    Tensor<int32_t> t3({1,2,3,4,5});
}

TEST(GTtest, CanInitializeFloat){
    Tensor<float> t({1,2,3,4.55555,5,99.78888});
}

TEST(GTtest, HasCorrectSize){
    Tensor<float> t({111.333,23.4444,3,4,5,99.78888});
    size_t EXPECTED_SIZE = 6;
    size_t ACTUAL_SIZE = t.size();

    ASSERT_EQ(EXPECTED_SIZE, ACTUAL_SIZE);
}


TEST(GTtest, CanAdd){
    Tensor<float> t1({1,2,3,4,5});
    Tensor<float> t2({1,2,3,4,5});
    Tensor<float> t3 = t1+t2;
}


TEST(GTtest, CanAddSingleElementTensorCorrectly){
    Tensor<int> t1({1,2,3,4,5});
    Tensor<int> t2({100});
    Tensor<int> ACTUAL1 = t1+t2;
    Tensor<int> EXPECTED1 = {101,102,103,104,105};


    Tensor<float> t3({1.11,22.22,2.3,4.4,5.778});
    Tensor<float> t4({100});
    Tensor<float> ACTUAL2 = t3+t4;
    Tensor<float> EXPECTED2 = {101.11,122.22,102.3,104.45,105.778};

    ASSERT_TRUE(EXPECTED1 == ACTUAL1);
    ASSERT_FALSE(ACTUAL1 == t1);     // test if t1 is not modified in place
    ASSERT_FALSE(EXPECTED2 == ACTUAL2);
    ASSERT_FALSE(ACTUAL2 == t3);     // test if t3 is not modified in place
}


TEST(GTtest, CanSubtractSingleElementTensorCorrectly){
    Tensor<int> t1({1,2,3,4,5});
    Tensor<int> t2({100});
    Tensor<int> ACTUAL1 = t1-t2;
    Tensor<int> EXPECTED1 = {-99,-98,-97,-96,-95};


    Tensor<float> t3({1.11,22.22,2.3,4.4});
    Tensor<float> t4({100});
    Tensor<float> ACTUAL2 = t3-t4;
    Tensor<float> EXPECTED2 = {-98.89,-77.78,-97.7,-95.6};
    ASSERT_TRUE(EXPECTED1 == ACTUAL1);
    ASSERT_FALSE(ACTUAL1 == t1);     // test if t1 is not modified in place
    ASSERT_TRUE(EXPECTED2 == ACTUAL2);
    ASSERT_FALSE(ACTUAL2 == t3);     // test if t3 is not modified in place
}

TEST(GTtest, CanAddMultiElementTensorCorrectly){
    Tensor<int> t1({1,2,3,4,5});
    Tensor<int> t2({1,2,3,4,5});
    Tensor<int> ACTUAL = t1+t2;
    Tensor<int> EXPECTED = {2,4,6,8,10};

    ASSERT_TRUE(EXPECTED == ACTUAL);

}

TEST(GTtest, CanAddMultiElementTensorCorrectlyInPlace){
    Tensor<int> t1({1,2,3,4,5});
    Tensor<int> t2({1,2,3,4,5});
    Tensor<int> ACTUAL = t1.plus(t2);
    Tensor<int> EXPECTED = {2,4,6,8,10};

    ASSERT_TRUE(EXPECTED == ACTUAL);
    ASSERT_TRUE(EXPECTED == t1);     // test if t1 is modified in place
}

TEST(GTtest, OverloadSquareBracketOperatorTensor){
    Tensor<float> t1({1,-22.2,3,4,5});
    float EXPECTED_SECOND_ELEMENT_t1 = -22.2;
    float ACTUAL_SECOND_ELEMENT_t1 = t1[1];

    Tensor<float> t2({1,2,43,-404,5});
    float EXPECTED_FOURTH_ELEMENT_t2 = -404;
    float ACTUAL_FOURTH_ELEMENT_t2 = t2[3];


    ASSERT_EQ(EXPECTED_SECOND_ELEMENT_t1, ACTUAL_SECOND_ELEMENT_t1);
    ASSERT_EQ(EXPECTED_FOURTH_ELEMENT_t2, ACTUAL_FOURTH_ELEMENT_t2);
}


TEST(GTtest, CanMultiplyInPlace){
    Tensor<float> t1({0,1,22,33,4});
    Tensor<float> t2({0,1,2,3,4});
    Tensor<float> ACTUAL_1 = t1.multiply(t2);
    Tensor<float> EXPECTED_1 = {0,1,44,99,16};
    ASSERT_TRUE(EXPECTED_1 == ACTUAL_1);
    ASSERT_TRUE(t1 == ACTUAL_1); // should modify t1 in place

}