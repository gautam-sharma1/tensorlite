//
// Created by Gautam Sharma on 9/12/21.
//



#include "Tensor.h"
#include <iostream>
using namespace std;

int main(){
    Tensor<double> t1  = {{1,2,3,4}};
    Tensor<double> t2 = {{5,6,7,8}};
    Tensor<double> t3 = t1+t2;
    cout << t3 << endl;

}