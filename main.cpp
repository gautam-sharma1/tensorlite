//
// Created by Gautam Sharma on 9/12/21.
//
#include "Tensor.h"
#include "Tensor2D.h"
#include "Layer.h"
#include <iostream>
using namespace std;

int main(){


    Tensor<double> t1  = {{1,2,3,4}};
    Tensor<double> t2 = {{5,6,7,8}};
    Tensor<double> t3 = t1+t2;
    cout << t3 << endl;
    // vector<Tensor<double>> t4 = {t1,t1,t1};
    Tensor2D<double> t5({t1,t1,t1,t2,t2,t1,t2,t1,t2,t1,t2});
    Tensor2D<double> tt(t5);
    cout << t5 << endl;
    auto t6 = t5.transpose();
    cout <<  t6 << endl;
    auto t7 = t5*t6;
    cout << t7 << endl;
    Layer<double> l1(5,5);
    cout << l1 << endl;
    l1.multiply(100);
    cout << l1 << endl;
    Layer<double> l2 (5,1);
    cout << l2 <<endl;
    Layer<double> ll = l1.multiply(l2);
    cout << ll << endl;
    cout << l1 << endl;

    Layer<double> l3 (5,1);
    cout << l3 << endl;
    auto sigmoid_tensor = l3.sigmoid();

    cout << sigmoid_tensor << endl;




}