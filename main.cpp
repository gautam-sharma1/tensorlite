//
// Created by Gautam Sharma on 9/12/21.
//
#include "include/Tensor.h"
#include <iostream>
using namespace std;

int main(){

    Tensor<float> t ({1,2.555,3,4,5,6.667,7,8});
    cout << t << endl;
    cout << "Done!" << endl;
}