
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
  cd build
  cmake .. && make
```

## Demo

Insert gif or link to demo


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

// Output { 6,8,10,12 }
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
Layer<float> l(5,5);


```






## Running Tests

To run tests, run the following command

```bash
  npm run test
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

  