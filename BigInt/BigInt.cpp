#include "BigInt.h"

BigInt::BigInt() {
    BASE_LENGTH = (int)log10(BASE);
	digits.push_back(0);
}

BigInt::BigInt(std::string value) {
    BASE_LENGTH = (int)log10(BASE);
	if (value.empty()) digits.push_back(0);
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

auto operator+(BigInt l, BigInt r) -> BigInt {
	if (l.isNegative && !r.isNegative) return (r - (-l));
	if (!l.isNegative && r.isNegative) return (l - (-r));
	if (l.isNegative && r.isNegative) return -((-l) + (-r));
	
	BigInt result;
	int carrier = 0, x = 0, y = 0, sum = 0;
	for (size_t i = 0; i < std::max(l.digits.size(), r.digits.size()); i++) {
		x = (i < l.digits.size()) ? l.digits[i] : 0;
		y = (i < r.digits.size()) ? r.digits[i] : 0;
		sum = x + y + carrier;

		if (i < result.digits.size()) result.digits[i] = sum % l.BASE;
		else result.digits.push_back(sum % l.BASE);

		carrier = sum >= l.BASE;
	}
	if (carrier > 0) result.digits.push_back(carrier);
	return result.removeZeros();
}

auto operator-(BigInt l, BigInt r) -> BigInt {
	if (r.isNegative) return l + (-r);
	if (l.isNegative && !r.isNegative) return -((-l) + r);
	if (l < r) return -(r - l);
	if (l == r) return BigInt();

	BigInt result;
    int carrier = 0, diff = 0;
	for (size_t i = 0; i < l.digits.size(); i++) {
		diff = l.digits[i] - carrier - (i < r.digits.size() ? r.digits[i] : 0);
		if (diff < 0) {
			carrier = 1;
			diff += l.BASE;
		}
		else carrier = 0;
		if (result.digits.size() > i) result.digits[i] = diff;
		else result.digits.push_back(diff);
	}

	if (carrier > 0) result.digits.push_back(carrier);
	return result.removeZeros();
}

auto operator*(const BigInt &l,const BigInt& r) -> BigInt {
    return BigInt::karatsubaMultiply(l, r);
}

auto BigInt::operator=(const BigInt& r) -> BigInt& = default;

auto BigInt::operator=(std::string r) -> BigInt& {
    BigInt temp(std::move(r));
    *this = temp;
    return *this;
}

auto operator<(BigInt& l,BigInt& r) -> bool {
	if (l.isNegative && !r.isNegative) return true;
	else if (!l.isNegative && r.isNegative) return false;
	else if (l.isNegative && r.isNegative) return !((-l) < (-r));
	else {
		if (l.digits.size() < r.digits.size()) return true;
		else if (l.digits.size() > r.digits.size()) return false;
		else {
		    auto l_it = l.digits.rbegin();
		    auto r_it = r.digits.rbegin();
			while (l_it != l.digits.rend()) {
				if (*l_it < *r_it) return true;
				else if (*l_it > *r_it) return false;
				l_it++;	r_it++;
			}
			return false;
		}
	}
}

auto operator>(BigInt& l, BigInt& r) -> bool {
	return r < l;
}

auto operator==(BigInt& l, BigInt& r) -> bool {
	return (!(l < r) && !(l > r));
}

auto BigInt::operator-() -> BigInt& {
	isNegative = !isNegative;
	return *this;
}

auto BigInt::operator+() -> BigInt& {
	return *this;
}

auto operator<<(std::ostream& os,const BigInt& num) -> std::ostream& {
	if (num.isNegative) os << '-';
	std::cout << num.digits[num.digits.size() - 1];
	for (auto i = num.digits.rbegin() + 1; i != num.digits.rend(); i++) {
		std::cout << std::setfill('0') << std::setw(num.BASE_LENGTH) << *i;
	}
	return os;
}

auto operator>>(std::istream& os, BigInt& num) -> std::istream& {
	std::string input;
	os >> input;
	num = BigInt(input);
	return os;
}

auto BigInt::str() -> std::string {
	std::string result, strValue;
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

auto BigInt::removeZeros() -> BigInt& {
	while (digits.back() == 0 && digits.size() > 1) digits.pop_back();
	if (digits.size() == 1 && digits[0] == 0) isNegative = false;
	return *this;
}

auto BigInt::schoolMultiply(BigInt l, BigInt r) -> BigInt {
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

auto BigInt::karatsubaMultiply(BigInt l, BigInt r) -> BigInt {
    if ((l.digits.size() == 1 && l.digits[0] == 0) || (r.digits.size() == 1 && r.digits[0] == 0)) return BigInt("0");
    if (l.isNegative && !r.isNegative) return -karatsubaMultiply((-l), r);
    if (!l.isNegative && r.isNegative) return -karatsubaMultiply(l, (-r));
    if (l.isNegative && r.isNegative) return karatsubaMultiply((-l), (-r));

    BigInt shorter = l.digits.size() < r.digits.size() ? l : r,
           longer  = l.digits.size() < r.digits.size() ? r : l;

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

typedef std::complex<double> complex;
void fft (std::vector<complex> & a, bool invert) {
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
        complex wlen(cos(ang), sin(ang));
        for (size_t i = 0; i < n; i += len) {
            complex w(1);
            for (size_t j = 0; j < len/2; ++j) {
                complex u = a[i+j],  v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (size_t i = 0; i < n; i++) a[i] /= n;
    }
}

auto BigInt::FFTMultiply(BigInt l, BigInt r) -> BigInt {
    if ((l.digits.size() == 1 && l.digits[0] == 0) || (r.digits.size() == 1 && r.digits[0] == 0)) return BigInt("0");
    if (l.isNegative && !r.isNegative) return -FFTMultiply((-l), r);
    if (!l.isNegative && r.isNegative) return -FFTMultiply(l, (-r));
    if (l.isNegative && r.isNegative) return FFTMultiply((-l), (-r));

    size_t n = 1, max = std::max(l.digits.size(), r.digits.size());
    std::vector<complex> fa(l.digits.begin(), l.digits.end()),
                         fb(r.digits.begin(), r.digits.end());

    while (n < max) n *= 2;
    n *= 2;

    fa.resize(n),  fb.resize(n);

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

auto BigInt::multiplyByInt(BigInt l, int r) -> BigInt {
    if (r > l.BASE || r < 0) return l;
    BigInt result;
    if (l.isNegative) result.isNegative = true;
    int carrier = 0, multi = 0;
    for (size_t i = 0; i < l.digits.size(); i++) {
        multi = l.digits[i]*r + carrier;
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
