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
    int BASE = 1E2;
    int BASE_LENGTH;
    bool isNegative = false;
    std::deque<long long> digits;
public:
    BigInt();
    explicit BigInt(std::string value);

    friend auto operator<<(std::ostream& os,const BigInt& num) -> std::ostream&;
    friend auto operator>>(std::istream& os, BigInt& num) -> std::istream&;
    friend auto operator+(BigInt l, BigInt r) -> BigInt;
    friend auto operator-(BigInt l, BigInt r) -> BigInt;
    friend auto operator*(BigInt l, BigInt r) -> BigInt;
    friend auto operator<(const BigInt& l,const BigInt& r) -> bool;
    friend auto operator>(const BigInt& l,const BigInt& r) -> bool;
    friend auto operator==(const BigInt& l,const BigInt& r) -> bool;

    auto operator-() -> BigInt&;
    auto operator+() -> BigInt&;
    auto operator=(const BigInt& r) -> BigInt&;
    auto operator=(std::string r) -> BigInt&;
    auto str() -> std::string;
    auto removeZeros() -> BigInt&;

    static auto schoolMultiply(const BigInt& l, BigInt r) -> BigInt;
    static auto karatsubaMultiply(const BigInt& l, const BigInt& r) -> BigInt;
    static auto FFTMultiply(const BigInt& l, const BigInt& r) -> BigInt;
    static auto multiplyByLongLong(const BigInt& l, long long r) -> BigInt;
};

#endif