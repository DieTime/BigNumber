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
		for (long long i = value.length(); i > 0; i -= BigInt::BASE_LENGTH) {
			if (i < BigInt::BASE_LENGTH) digits.push_back(strtol(value.substr(0, i).c_str(), nullptr, 10));
			else digits.push_back(strtol(value.substr(i - BigInt::BASE_LENGTH, BigInt::BASE_LENGTH).c_str(), nullptr, 10));
		}
		this->removeZeros();
	}
}

auto operator+(BigInt l, BigInt r) -> BigInt {
	if (l.isNegative && !r.isNegative) return (r - (-l));
	if (!l.isNegative && r.isNegative) return (l - (-r));
	if (l.isNegative && r.isNegative) return -((-l) + (-r));
	BigInt result;
	long long carrier = 0, x = 0, y = 0, sum = 0;
	for (long long i = 0; i < std::max(l.digits.size(), r.digits.size()); i++) {
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
    long long carrier = 0, diff = 0;
	for (long long i = 0; i < l.digits.size(); i++) {
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

auto operator*(const BigInt& l, const BigInt& r) -> BigInt {
    long long length = std::max(l.digits.size(), r.digits.size()) * l.BASE_LENGTH;
    if (length < 585) return BigInt::schoolMultiply(l, r);
    else if (length >=585 && length < 995) return BigInt::karatsubaMultiply(l, r);
    else return BigInt::FFTMultiply(l, r);
}

auto BigInt::operator=(const BigInt& r) -> BigInt& = default;

auto BigInt::operator=(std::string r) -> BigInt& {
    BigInt temp(std::move(r));
    *this = temp;
    return *this;
}

auto operator<(BigInt& l, BigInt& r) -> bool {
	if (l.isNegative && !r.isNegative) return true;
	else if (!l.isNegative && r.isNegative) return false;
	else {
		if (l.digits.size() < r.digits.size()) return true;
		else if (l.digits.size() > r.digits.size()) return false;
		else {
			for (long long i = l.digits.size() - 1; i >= 0; i--) {
				if (l.digits[i] < r.digits[i]) return true;
				else if (l.digits[i] > r.digits[i]) return false;
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

auto operator<<(std::ostream& os, BigInt num) -> std::ostream& {
	if (num.isNegative) os << "-";
	std::cout << num.digits[num.digits.size() - 1];
	for (long long i = num.digits.size() - 2; i >= 0; i--) {
		std::cout << std::setfill('0') << std::setw(num.BASE_LENGTH) << num.digits[i];
	}
	return os;
}

auto operator>>(std::istream& os, BigInt& num) -> std::istream& {
	std::string input;
	os >> input;
	BigInt newValue(input);
	num.BASE = newValue.BASE;
	num.isNegative = newValue.isNegative;
	num.digits = newValue.digits;
	return os;
}

auto BigInt::str() -> std::string {
	std::string result, strValue;
	if (isNegative) result += "-";
	strValue = std::to_string(digits[digits.size() - 1]);
	result += strValue;
	for (long long i = digits.size() - 2; i >= 0; i--) {
		strValue = std::to_string(digits[i]);
		for (long long j = strValue.size(); j < BigInt::BASE_LENGTH; j++) {
			result += "0";
		}
		result += strValue;
	}
	return result;
}

auto BigInt::removeZeros() -> BigInt {
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
    for (long long i = 0; i < r.digits.size(); i++) {
        temp = multiplyByUint(l, r.digits[i]);
        for (long long j = 0; j < i; j++) {
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

    const BigInt min = l.digits.size() < r.digits.size() ? l : r,
                 max = l.digits.size() < r.digits.size() ? r : l;

    if (min.digits.size() < 64) return schoolMultiply(max, min);
    else {
        long long n = max.digits.size() / 2;
        BigInt max1, max2, min1, min2;
        max1.digits = {max.digits.begin() + n, max.digits.end()};
        max2.digits = {max.digits.begin(), max.digits.begin() + n};
        min1.digits = {min.digits.begin() + n, min.digits.end()};
        min2.digits = {min.digits.begin(), min.digits.begin() + n};

        max1.removeZeros(); max2.removeZeros();
        min1.removeZeros(); min2.removeZeros();

        BigInt max1min1 = karatsubaMultiply(max1, min1),
               max2min2 = karatsubaMultiply(max2, min2),
               max1max2min2min1 = schoolMultiply((max1 - max2), (min2 - min1));

        BigInt left;
        left.digits.resize(n * 2);
        left.digits.insert(left.digits.end(), max1min1.digits.begin(), max1min1.digits.end());

        BigInt middleSum = max1max2min2min1 + max1min1 + max2min2;
        BigInt middle;
        middle.digits.resize(n);
        middle.digits.insert(middle.digits.end(), middleSum.digits.begin(), middleSum.digits.end());

        BigInt result = left + middle + max2min2;
        return result.removeZeros();
    }
}

void FFT(std::vector<base>& a, bool invert) {
    int n = (int) a.size();
    if (n == 1) return;

    std::vector<base> a0 (n/2),  a1 (n/2);
    for (long long i=0, j=0; i<n; i+=2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i+1];
    }
    FFT(a0, invert);
    FFT(a1, invert);

    double ang = 2 * 3.14159265358979323846 / n * (invert ? -1 : 1);
    base w (1),  wn (cos(ang), sin(ang));
    for (long long i=0; i<n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if (invert)
            a[i] /= 2,  a[i+n/2] /= 2;
        w *= wn;
    }
}

auto BigInt::FFTMultiply(BigInt l, BigInt r) -> BigInt {
    if ((l.digits.size() == 1 && l.digits[0] == 0) || (r.digits.size() == 1 && r.digits[0] == 0)) return BigInt("0");
    if (l.isNegative && !r.isNegative) return -FFTMultiply((-l), r);
    if (!l.isNegative && r.isNegative) return -FFTMultiply(l, (-r));
    if (l.isNegative && r.isNegative) return FFTMultiply((-l), (-r));

    long long n = 1;
    std::vector<base> fa(l.digits.begin(), l.digits.end()), fb(r.digits.begin(), r.digits.end());
    while (n < std::max(l.digits.size(), r.digits.size())) n *= 2;
    n *= 2;

    fa.resize(n),  fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);

    for (long long i=0; i<n; ++i) fa[i] *= fb[i];
    FFT(fa, true);

    BigInt result;
    result.digits.resize(n);

    for (long long i=0; i<n; ++i)
        result.digits[i] = (long long)(fa[i].real() + 0.5);

    long long carry = 0;
    for (long long i=0; i<n; ++i) {
        result.digits[i] += carry;
        carry = result.digits[i] / result.BASE;
        result.digits[i] %= result.BASE;
    }

    return result.removeZeros();
}

auto BigInt::multiplyByLongLong(BigInt l, long long r) -> BigInt {
    if (r > l.BASE) return l;
    BigInt result;
    if (l.isNegative) result.isNegative = true;
    long long carrier = 0, multi = 0;
    for (long long i = 0; i < l.digits.size(); i++) {
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
