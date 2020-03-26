#include "BigInt.h"

BigInt::BigInt() {
    BASE_LENGTH = (int)log10(BASE);
    digits.push_back(0);
}

BigInt::BigInt(std::string value) {
    BASE_LENGTH = (int)log10(BASE);
    if (value.empty()) digits.push_back(0);
    else if (value == "NaN") digits.push_back(std::numeric_limits<int>::quiet_NaN());
    else {
        if (value[0] == '-') {
            isNegative = true;
            value = value.substr(1);
        }

        while (!value.empty()) {
            int i = 0;
            std::string str;
            while (!value.empty() && i < BASE_LENGTH) {
                str.push_back(value.back());
                value.pop_back();
                i++;
            }
            std::reverse(str.begin(), str.end());
            digits.push_back(strtol(str.c_str(), nullptr, 10));
        }

        removeZeros();
    }
}

std::ostream & operator<<(std::ostream &os, BigInt num) {
    os << num.str();
    return os;
}

std::istream & operator>>(std::istream &os, BigInt& num) {
    std::string input;
    os >> input;
    num = BigInt(input);
    return os;
}

BigInt operator+(const BigInt &l, const BigInt &r) {
    if (l.isNegative && !r.isNegative) return (r - (-l));
    if (!l.isNegative && r.isNegative) return (l - (-r));
    if (l.isNegative && r.isNegative) return -((-l) + (-r));
    if (l < r) return r + l;

    BigInt result;
    result.digits.resize(l.digits.size());
    int carrier = 0, sum = 0;
    for (size_t i = 0; i < std::max(l.digits.size(), r.digits.size()); i++) {
        sum = l.digits[i] +  (i < r.digits.size() ? r.digits[i] : 0) + carrier;
        result.digits[i] = sum % l.BASE;
        carrier = sum >= l.BASE;
    }
    result.digits.push_back(carrier);
    return result.removeZeros();
}

BigInt operator-(const BigInt &l, const BigInt &r) {
    if (l == r) return BigInt("0");
    if (r.isNegative) return l + (-r);
    if (l.isNegative && !r.isNegative) return -((-l) + r);
    if (l < r) return -(r - l);

    BigInt result;
    result.digits.resize(l.digits.size());
    int loan = 0, diff = 0;
    for (size_t i = 0; i < l.digits.size(); i++) {
        diff = l.digits[i] - loan - (i < r.digits.size() ? r.digits[i] : 0);
        loan = diff < 0;
        if (diff < 0) diff += l.BASE;
        result.digits[i] = diff;
    }
    return result.removeZeros();
}

BigInt operator*(const BigInt &l, const BigInt &r) {
    return BigInt::FFTMultiply(l, r);
}

BigInt operator/(const BigInt &l, const BigInt &r) {
    return BigInt::schoolDivision(l, r);
}

bool operator<(const BigInt &l, const BigInt &r) {
    if (l.isNegative && !r.isNegative) return true;
    if (!l.isNegative && r.isNegative) return false;
    if (l.isNegative && r.isNegative) return (-l) > (-r);
    if (l.digits.size() < r.digits.size()) return true;
    if (l.digits.size() > r.digits.size()) return false;
    auto l_it = l.digits.rbegin();
    auto r_it = r.digits.rbegin();
    while (l_it != l.digits.rend()) {
        if (*l_it < *r_it) return true;
        if (*l_it > *r_it) return false;
        l_it++;
        r_it++;
    }
    return false;
}

bool operator<=(const BigInt &l, const BigInt &r) {
    return ((l < r) || (l == r));
}

bool operator>(const BigInt &l, const BigInt &r) {
    return r < l;
}

bool operator>=(const BigInt &l, const BigInt &r) {
    return ((l > r) || (l == r));
}

bool operator==(const BigInt &l, const BigInt &r) {
    if (!l.isNegative && r.isNegative) return false;
    if (l.isNegative && !r.isNegative) return false;
    if (l.digits.size() != r.digits.size()) return false;
    auto l_it = l.digits.rbegin();
    auto r_it = r.digits.rbegin();
    while (l_it != l.digits.rend()) {
        if (*l_it != *r_it) return false;
        l_it++;
        r_it++;
    }
    return true;
}

bool operator!=(const BigInt &l, const BigInt &r) {
    return !(l == r);
}

BigInt& BigInt::operator=(std::string r) {
    BigInt temp(std::move(r));
    *this = temp;
    return *this;
}

BigInt& BigInt::operator=(const BigInt &r) {
    if (this == &r) return *this;
    BASE = r.BASE;
    BASE_LENGTH = r.BASE_LENGTH;
    digits = r.digits;
    isNegative = r.isNegative;
    return *this;
}

BigInt BigInt::operator+() const & {
    return *this;
}

BigInt BigInt::operator-() const & {
    BigInt b = *this;
    b.isNegative = !b.isNegative;
    return b;
}

BigInt & BigInt::operator++() {
    *this = *this + BigInt("1");
    return *this;
}

BigInt & BigInt::operator--() {
    *this = *this - BigInt("1");
    return *this;
}

const BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    *this = *this + BigInt("1");
    return temp;
}

const BigInt BigInt::operator--(int) {
    BigInt temp = *this;
    *this = *this - BigInt("1");
    return temp;
}

std::string BigInt::str() {
    std::string result, strValue;
    if (digits.size() == 1 && digits.back() == std::numeric_limits<int>::quiet_NaN()) return "NaN";
    if (isNegative) result += "-";
    strValue = std::to_string(digits[digits.size() - 1]);
    result += strValue;
    for (auto i = digits.rbegin() + 1; i != digits.rend(); i++) {
        strValue = std::to_string(*i);
        for (size_t j = strValue.size(); j < BASE_LENGTH; j++) result += "0";
        result += strValue;
    }
    return result;
}

BigInt& BigInt::removeZeros() {
    while (digits.back() == 0 && digits.size() > 1) digits.pop_back();
    if (digits.size() == 1 && digits[0] == 0) isNegative = false;
    return *this;
}

BigInt BigInt::abs(const BigInt &value) {
    BigInt result = value;
    result.isNegative = false;
    return result;
}

BigInt BigInt::multiplyByInt(const BigInt& l, int r) {
    if (r > l.BASE || r < 0) return l;
    BigInt result;
    if (l.isNegative) result.isNegative = true;
    int carrier = 0, multi = 0;
    for (size_t i = 0; i < l.digits.size(); i++) {
        multi = l.digits[i] * r + carrier;
        carrier = multi / l.BASE;
        multi %= l.BASE;
        if (i < result.digits.size()) result.digits[i] = multi;
        else result.digits.push_back(multi);
    }
    while (carrier != 0) {
        result.digits.push_back(carrier % result.BASE);
        carrier /= result.BASE;
    }
    return result.removeZeros();
}

BigInt BigInt::schoolMultiply(const BigInt& l, const BigInt &r) {
    if ((l.digits.size() == 1 && l.digits[0] == 0) || (r.digits.size() == 1 && r.digits[0] == 0)) return BigInt("0");
    if (l.isNegative && !r.isNegative) return -schoolMultiply((-l), r);
    if (!l.isNegative && r.isNegative) return -schoolMultiply(l, (-r));
    if (l.isNegative && r.isNegative) return schoolMultiply((-l), (-r));

    BigInt result, temp;
    for (size_t i = 0; i < r.digits.size(); i++) {
        temp = multiplyByInt(l, r.digits[i]);
        for (size_t j = 0; j < i; j++) {
            temp.digits.push_front(0);
        }
        result = result + temp;
    }
    return result.removeZeros();
}

BigInt BigInt::karatsubaMultiply(const BigInt& l, const BigInt& r) {
    if ((l.digits.size() == 1 && l.digits[0] == 0) || (r.digits.size() == 1 && r.digits[0] == 0)) return BigInt("0");
    if (l.isNegative && !r.isNegative) return -karatsubaMultiply((-l), r);
    if (!l.isNegative && r.isNegative) return -karatsubaMultiply(l, (-r));
    if (l.isNegative && r.isNegative) return karatsubaMultiply((-l), (-r));

    BigInt shorter = l.digits.size() < r.digits.size() ? l : r,
            longer = l.digits.size() < r.digits.size() ? r : l;

    if (shorter.digits.size() * shorter.BASE_LENGTH < 128) return schoolMultiply(longer, shorter);

    size_t n = longer.digits.size() / 2;
    BigInt l1, l2, s1, s2;

    l1.digits = {longer.digits.begin() + n, longer.digits.end()};
    l2.digits = {longer.digits.begin(), longer.digits.begin() + n};
    if (shorter.digits.size() > n) {
        s1.digits = {shorter.digits.begin() + n, shorter.digits.end()};
        s2.digits = {shorter.digits.begin(), shorter.digits.begin() + n};
    } else {
        s2.digits = shorter.digits;
    }

    l2.removeZeros();
    s2.removeZeros();

    BigInt P1 = karatsubaMultiply(l1, s1);
    BigInt P2 = karatsubaMultiply(l2, s2);
    BigInt P3 = karatsubaMultiply((l1 - l2), (s2 - s1)) + P1 + P2;

    for (size_t i = 0; i < n * 2; i++) P1.digits.push_front(0);
    for (size_t i = 0; i < n; i++) P3.digits.push_front(0);

    BigInt result = P1 + P3 + P2;
    return result.removeZeros();

}

void fft(std::vector<std::complex<double>> &a, bool invert) {
    size_t n = a.size();
    const double PI = 3.14159265358979323846;

    for (size_t i = 1, j = 0; i < n; i++) {
        size_t bit = n / 2;
        while (j >= bit) {
            j -= bit;
            bit /= 2;
        }
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (size_t len = 2; len <= n; len *= 2) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        std::complex<double> wlen(cos(ang), sin(ang));
        for (size_t i = 0; i < n; i += len) {
            std::complex<double> w(1);
            for (size_t j = 0; j < len / 2; ++j) {
                std::complex<double> u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (size_t i = 0; i < n; i++) a[i] /= n;
    }
}

BigInt BigInt::FFTMultiply(const BigInt& l, const BigInt& r) {
    if ((l.digits.size() == 1 && l.digits[0] == 0) || (r.digits.size() == 1 && r.digits[0] == 0)) return BigInt("0");
    if (l.isNegative && !r.isNegative) return -FFTMultiply((-l), r);
    if (!l.isNegative && r.isNegative) return -FFTMultiply(l, (-r));
    if (l.isNegative && r.isNegative) return FFTMultiply((-l), (-r));

    size_t n = 1, max = std::max(l.digits.size(), r.digits.size());
    std::vector<std::complex<double>> fa(l.digits.begin(), l.digits.end()),
            fb(r.digits.begin(), r.digits.end());

    while (n < max) n *= 2;
    n *= 2;

    fa.resize(n), fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (size_t i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    BigInt result;
    result.digits.resize(n);

    for (size_t i = 0; i < n; i++)
        result.digits[i] = ceil(fa[i].real() * 2) / 2;

    int carry = 0;
    for (size_t i = 0; i < n; i++) {
        result.digits[i] += carry;
        carry = result.digits[i] / result.BASE;
        result.digits[i] %= result.BASE;
    }

    return result.removeZeros();
}

int BigInt::findDiv(const BigInt &l, const BigInt &r) {
    int first = 0, last = l.BASE;
    int count = last - first, step, it;
    while (count > 0) {
        step = count / 2;
        it = first + step;
        if (l >= multiplyByInt(r, it)) {
            first = ++it;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    return first - 1;
}

BigInt BigInt::schoolDivision(const BigInt &l, const BigInt &r) {
    if (abs(l) < abs(r)) return BigInt("0");
    if (r == BigInt("1")) return l;
    if (r == BigInt("0")) return BigInt("NaN");
    if (l.isNegative && !r.isNegative) return -schoolDivision(-l, r);
    if (!l.isNegative && r.isNegative) return -schoolDivision(l, -r);
    if (l.isNegative && r.isNegative) return schoolDivision(-l, -r);
    if (l == r) return BigInt("1");

    BigInt result, memory;
    memory.digits.clear();
    result.digits.clear();

    for (size_t i = 0; i < l.digits.size(); i++) {
        memory.digits.push_front(l.digits[l.digits.size() - 1 - i]);
        int div = findDiv(memory, r);
        result.digits.push_front(div);
        memory = memory - multiplyByInt(r, div);
        if (memory.digits.size() == 1 && memory.digits[0] == 0) memory.digits.clear();
    }

    return result.removeZeros();
}



