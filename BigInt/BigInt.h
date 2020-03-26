#pragma once

#ifndef BIG_INT
#define BIG_INT

#include <algorithm>
#include <cmath>
#include <complex>
#include <deque>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <utility>
#include <vector>

class BigInt {
private:
    int BASE = 1E2;
    int BASE_LENGTH;
    bool isNegative = false;
    std::deque<int> digits;
public:
    BigInt();
    explicit BigInt(std::string value);

    friend std::ostream & operator<<(std::ostream& os, BigInt num);
    friend std::istream & operator>>(std::istream& os, BigInt& num);
    friend BigInt operator+(const BigInt &l, const BigInt &r);
    friend BigInt operator-(const BigInt &l, const BigInt &r);
    friend BigInt operator*(const BigInt &l, const BigInt &r);
    friend BigInt operator/(const BigInt &l, const BigInt &r);
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
    BigInt & operator++();
    BigInt & operator--();
    const BigInt operator++(int);
    const BigInt operator--(int);

    std::string str();
    BigInt & removeZeros();
    static BigInt abs(const BigInt &value);

    static BigInt multiplyByInt(const BigInt& l, int r);
    static BigInt schoolMultiply(const BigInt& l, const BigInt& r);
    static BigInt karatsubaMultiply(const BigInt& l, const BigInt& r);
    static BigInt FFTMultiply(const BigInt& l, const BigInt& r);

    static int findDiv(const BigInt & l, const BigInt &r);
    static BigInt schoolDivision(const BigInt & l, const BigInt & r);
};

#endif