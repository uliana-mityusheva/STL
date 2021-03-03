#include <iostream>
#include <numeric>
#include "rational.h"

int Gcd(int first, int second) {
    if (second < 0) {
        second *= -1;
    }
    if (first < 0) {
        first *= -1;
    }

    if (first < second) {
        std::swap(first, second);
    }
    while (first % second != 0) {
        first = first % second;
        if (first < second) {
            std::swap(first, second);
        }
    }
    return second;
}

int Lcm(int first, int second) {
    return (first * second) / Gcd(first, second);
}

void Rational::Reduce() {
    if (denominator == 0) {
        throw RationalDivisionByZero{};
    }

    int gcd = Gcd(numerator, denominator);
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
    numerator /= gcd;
    denominator /= gcd;
}

Rational::Rational() : numerator(0), denominator(1) {
}

Rational::Rational(int x) : numerator(x), denominator(1) {
}

Rational::Rational(int x, int y) {
    numerator = x;
    denominator = y;
    Reduce();
}

int Rational::GetNumerator() const {
    return numerator;
}

int Rational::GetDenominator() const {
    return denominator;
}

void Rational::SetNumerator(int num) {
    numerator = num;
    Reduce();
}

void Rational::SetDenominator(int num) {
    denominator = num;
    Reduce();
}

std::istream &operator>>(std::istream &is, Rational &num) {
    const int MaxStringSize = 32;
    char str[MaxStringSize];
    is >> str;
    char *end_ptr;
    num.numerator = strtol(str, &end_ptr, 10);
    if (*end_ptr != 0) {
        ++end_ptr;
        num.denominator = strtol(end_ptr, &end_ptr, 10);
    } else {
        num.denominator = 1;
    }
    num.Reduce();
    return is;
}

std::ostream &operator<<(std::ostream &out, const Rational &num) {
    if (num.denominator != 1) {
        out << num.numerator << "/" << num.denominator;
    } else {
        out << num.numerator;
    }
    return out;
}

Rational &Rational::operator+=(Rational add) {
    this->numerator = (add.numerator * this->denominator + this->numerator * add.denominator) /
                      Gcd(this->denominator, add.denominator);
    this->denominator = Lcm(this->denominator, add.denominator);
    this->Reduce();
    return *this;
}

Rational &Rational::operator-=(Rational add) {
    add.numerator *= -1;
    *this += add;
    return *this;
}

Rational &Rational::operator*=(Rational add) {
    this->numerator = this->numerator * add.numerator;
    this->denominator = this->denominator * add.denominator;
    this->Reduce();
    return *this;
}

Rational &Rational::operator/=(Rational add) {
    std::swap(add.numerator, add.denominator);
    *this *= add;
    return *this;
}

Rational operator+(Rational first, Rational second) {
    first += second;
    return first;
}

Rational operator-(Rational first, Rational second) {
    first -= second;
    return first;
}

Rational operator*(Rational first, Rational second) {
    first *= second;
    return first;
}

Rational operator/(Rational first, Rational second) {
    first /= second;
    return first;
}

Rational operator+(Rational num) {
    return num;
}

Rational operator-(Rational num) {
    num *= -1;
    return num;
}

Rational &operator++(Rational &num) {
    num += 1;
    return num;
}

Rational &operator--(Rational &num) {
    num -= 1;
    return num;
}
Rational operator++(Rational &num, int) {
    Rational copy = num;
    num += 1;
    return copy;
}

Rational operator--(Rational &num, int) {
    Rational copy = num;
    num -= 1;
    return copy;
}

bool operator>(const Rational &first, const Rational &second) {
    bool ans = false;
    if (first.numerator * second.numerator < 0) {
        if (first.numerator > 0) {
            ans = true;
        }
    } else if (first.numerator * second.denominator > second.numerator * first.denominator) {
        ans = true;
    }
    return ans;
}

bool operator<(const Rational &first, const Rational &second) {
    return (second > first);
}

bool operator==(const Rational &first, const Rational &second) {
    return (!(first > second) && !(second > first));
}

bool operator!=(const Rational &first, const Rational &second) {
    return !(first == second);
}

bool operator>=(const Rational &first, const Rational &second) {
    return (first > second || first == second);
}

bool operator<=(const Rational &first, const Rational &second) {
    return (first < second || first == second);
}
