#pragma once

#ifndef BIG_INT
#define BIG_INT

#include <algorithm>
#include <cmath>
#include <complex>
#include <deque>
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>

class BigInt {
private:
    int BASE = 1E1;
    int BASE_LENGTH;
    bool isNegative = false;
    std::deque<int> digits;
public:
    BigInt();
    explicit BigInt(std::string value);

    friend std::ostream & operator<<(std::ostream& os, BigInt num);
    friend std::istream & operator>>(std::istream& os, BigInt num);
    friend BigInt operator+(const BigInt &l, const BigInt &r);
    friend BigInt operator-(const BigInt &l, const BigInt &r);
    friend BigInt operator*(const BigInt &l, const BigInt &r);
    friend bool operator<(const BigInt &l, const BigInt &r);
    friend bool operator<=(const BigInt &l, const BigInt &r);
    friend bool operator>(const BigInt &l, const BigInt &r);
    friend bool operator>=(const BigInt &l, const BigInt &r);
    friend bool operator==(const BigInt &l, const BigInt &r);
    friend bool operator!=(const BigInt &l,const BigInt &r);
    BigInt & operator=(std::string r);
    BigInt & operator=(const BigInt &r);
    BigInt operator+() const &;
    BigInt operator-() const &;

    std::string str();
    BigInt & removeZeros();

    static BigInt multiplyByInt(const BigInt& l, int r);
    static BigInt schoolMultiply(const BigInt& l, const BigInt& r);
    static BigInt karatsubaMultiply(const BigInt& l, const BigInt& r);
    static BigInt FFTMultiply(const BigInt& l, const BigInt& r);
};

#endif