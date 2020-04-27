# Big Integer Library
<p align="center">
  <img src="https://i.ibb.co/FbW0hFG/1.png" width="300">
</p>
<p align="center">
  <img src="https://img.shields.io/badge/version-1.0.0-b.svg?style=flat-square" alt="version">
</p>

### About
Library for mathematical calculations with long integers:
- Addition
- Subtraction
- Multiplication
- Division

### Features
- Karatsuba multiplication.
- FFT multiplication.
- Comparison of numbers.
- Getting the result in text form.
- Output to various streams

### Example
```cpp
#include <iostream>
#include <string>
#include "BigInt/BigInt.h"

using namespace std;

int main() {
    // Initialization
    BigInt A("192023372036854775807");
    BigInt B("19111111111111111111");

    cout << "A = " << A << endl;
    cout << "B = " << B << endl << endl;

    // Arithmetic operations
    cout << "Summation: " << A + B << endl;
    cout << "Subtraction : " << A - B << endl;
    cout << "Multiplication: " << A * B << endl;
    cout << "Division: " << A / B << endl << endl;

    // Special methods
    cout << "Karatsuba multiplication: " << BigInt::karatsubaMultiply(A, B) << endl;
    cout << "FFT multiplication: " << BigInt::FFTMultiply(A, B) << endl << endl;

    // Get string result
    string result = (A * B).str();

    // Comparison
    cout << "Result of comparing: ";
    if (A > B){
        cout << "A > B" << endl;
    } else if (A < B) {
         cout << "A < B" << endl;
    } else {
        cout << "A = B" << endl;
    }

    return 0;
}
```
