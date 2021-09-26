
# tensorlite

A lightweight C++ tensor library capable to perform extremely fast tensor computations.



## Features

- Made with ❤️ using modern C++
- Fully templated library
- Fully extensible
- Uses smart pointers for safe memory management
- Cross platform



## Installation

Install tensorlite as follows

```bash
  git clone 
  cd tensorlite
  make
```

[comment]: <> (## Demo)

[comment]: <> (Insert gif or link to demo)

## Usage/Examples

```cpp
#include "Tensor.h"
#include "Tensor2D.h"
#include "Layer.h"
#include <iostream>
using namespace std;


Tensor<double> t1  = {{1,2,3,4}};
Tensor<double> t2 = {{5,6,7,8}};
Tensor<double> t3 = t1+t2;
cout << t3 << endl;

output:{ 6,8,10,12 }
```

```cpp
Tensor2D<double> t5({t1,t1,t1,t2,t2,t1,t2,t1,t2,t1,t2});
cout << t5 << endl;

output:
Tensor2D {
{ 1,2,3,4 }
{ 1,2,3,4 }
{ 1,2,3,4 }
{ 5,6,7,8 }
{ 5,6,7,8 }
{ 1,2,3,4 }
{ 5,6,7,8 }
{ 1,2,3,4 }
{ 5,6,7,8 }
{ 1,2,3,4 }
{ 5,6,7,8 }
}
```

```cpp
auto t6 = t5.transpose();
cout <<  t6 << endl;

output:
Tensor2D {
{ 1,1,1,5,5,1,5,1,5,1,5 }
{ 2,2,2,6,6,2,6,2,6,2,6 }
{ 3,3,3,7,7,3,7,3,7,3,7 }
{ 4,4,4,8,8,4,8,4,8,4,8 }
 }
```

```cpp
auto t7 = t5*t6;
cout << t7 << endl;

output:
Tensor2D {
{ 30,30,30,70,70,30,70,30,70,30,70 }
{ 30,30,30,70,70,30,70,30,70,30,70 }
{ 30,30,30,70,70,30,70,30,70,30,70 }
{ 70,70,70,174,174,70,174,70,174,70,174 }
{ 70,70,70,174,174,70,174,70,174,70,174 }
{ 30,30,30,70,70,30,70,30,70,30,70 }
{ 70,70,70,174,174,70,174,70,174,70,174 }
{ 30,30,30,70,70,30,70,30,70,30,70 }
{ 70,70,70,174,174,70,174,70,174,70,174 }
{ 30,30,30,70,70,30,70,30,70,30,70 }
{ 70,70,70,174,174,70,174,70,174,70,174 }
}
```

```cpp
Layer<float> l(5,5);
cout << l1 << endl;
output:
Layer {
{ -1.15307,-0.228105,0.167813,0.86608,-0.62505 }
{ -0.294773,0.292243,-1.50031,0.93002,-0.470464 }
{ 0.838648,0.320883,-0.149071,-0.373821,-0.30948 }
{ 0.45579,-0.565829,-0.139341,-1.63598,0.288001 }
{ 0.674396,0.281527,-0.044332,-0.312636,1.20646 }
}
```

```cpp
l1.multiply(100);
output:
Layer {
{ -115.307,-22.8105,16.7813,86.608,-62.505 }
{ -29.4773,29.2243,-150.031,93.002,-47.0464 }
{ 83.8648,32.0883,-14.9071,-37.3821,-30.948 }
{ 45.579,-56.5829,-13.9341,-163.598,28.8001 }
{ 67.4396,28.1527,-4.4332,-31.2636,120.646 }
}
```

```cpp
Layer<double> l2 (5,1);
Layer<double> ll = l1.multiply(l2);
cout << ll << endl;
output:
Layer {
{ -44.5445 }
{ 200.929 }
{ 128.982 }
{ -51.4861 }
{ -38.3569 }
}
```






## Running Tests

To run tests, run the following command

```bash
  ./test_tensor
  ./test_tensor2D
```


## Contributing

Contributions are always welcome!

See `contributing.md` for ways to get started.

Please adhere to this project's `code of conduct`.

The following are some pressing features that need to be completed:

* ~~Make Layer class~~
* Activation Functions  
* Example for Forward Propagation
* Function to calculate gradients in back propagation  
* Support Multi-Threading and GPU computations

## Authors

- [@gautamsharma](https://www.github.com/gautam-sharma1)


## Appendix

Any additional information goes here


[comment]: <> (## API Reference)

[comment]: <> (#### Get all items)

[comment]: <> (```cpp)

[comment]: <> (   int i = 2)

[comment]: <> (```)

[comment]: <> (| Parameter | Type     | Description                |)

[comment]: <> (| :-------- | :------- | :------------------------- |)

[comment]: <> (| `api_key` | `string` | **Required**. Your API key |)

[comment]: <> (#### Get item)

[comment]: <> (```cpp)

[comment]: <> (  Tensor<int> t;)

[comment]: <> (  vector<int> )

[comment]: <> (```)

[comment]: <> (| Parameter | Type     | Description                       |)

[comment]: <> (| :-------- | :------- | :-------------------------------- |)

[comment]: <> (| `id`      | `string` | **Required**. Id of item to fetch |)

[comment]: <> (#### add&#40;num1, num2&#41;)

[comment]: <> (Takes two numbers and returns the sum.)

  