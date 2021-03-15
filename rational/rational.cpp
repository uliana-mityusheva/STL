#include <iostream>
#include <numeric>
#include "rational.h"

int Lcm(int first, int second) {
    return (first * second) / std::gcd(first, second);
}

void Rational::Reduce() {
    if (denominator_ == 0) {
        throw RationalDivisionByZero{};
    }

    int gcd = std::gcd(numerator_, denominator_);
    if (denominator_ < 0) {
        numerator_ *= -1;
        denominator_ *= -1;
    }
    numerator_ /= gcd;
    denominator_ /= gcd;
}

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int num) : numerator_(num), denominator_(1) {
}

Rational::Rational(int num, int den) {
    numerator_ = num;
    denominator_ = den;
    Reduce();
}

int Rational::GetNumerator() const {
    return numerator_;
}

int Rational::GetDenominator() const {
    return denominator_;
}

void Rational::SetNumerator(int fract) {
    numerator_ = fract;
    Reduce();
}

void Rational::SetDenominator(int fract) {
    denominator_ = fract;
    Reduce();
}

std::istream &operator>>(std::istream &is, Rational &fract) {
    const int MaxStringSize = 32;
    char str[MaxStringSize];
    is >> str;
    char *end_ptr;
    fract.numerator_ = strtol(str, &end_ptr, 10);
    if (*end_ptr != 0) {
        ++end_ptr;
        fract.denominator_ = strtol(end_ptr, &end_ptr, 10);
    } else {
        fract.denominator_ = 1;
    }
    fract.Reduce();
    return is;
}

std::ostream &operator<<(std::ostream &out, const Rational &fract) {
    if (fract.denominator_ != 1) {
        out << fract.numerator_ << "/" << fract.denominator_;
    } else {
        out << fract.numerator_;
    }
    return out;
}

Rational &Rational::operator+=(Rational other) {
    this->numerator_ = (other.numerator_ * this->denominator_ + this->numerator_ * other.denominator_) /
                      std::gcd(this->denominator_, other.denominator_);
    this->denominator_ = Lcm(this->denominator_, other.denominator_);
    this->Reduce();
    return *this;
}

Rational &Rational::operator-=(Rational other) {
    other.numerator_ *= -1;
    *this += other;
    return *this;
}

Rational &Rational::operator*=(Rational other) {
    this->numerator_ = this->numerator_ * other.numerator_;
    this->denominator_ = this->denominator_ * other.denominator_;
    this->Reduce();
    return *this;
}

Rational &Rational::operator/=(Rational other) {
    std::swap(other.numerator_, other.denominator_);
    *this *= other;
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

Rational operator+(Rational fract) {
    return fract;
}

Rational operator-(Rational fract) {
    fract *= -1;
    return fract;
}

Rational &operator++(Rational &fract) {
    fract += 1;
    return fract;
}

Rational &operator--(Rational &fract) {
    fract -= 1;
    return fract;
}
Rational operator++(Rational &fract, int) {
    Rational copy = fract;
    fract += 1;
    return copy;
}

Rational operator--(Rational &fract, int) {
    Rational copy = fract;
    fract -= 1;
    return copy;
}

bool operator>(const Rational &first, const Rational &second) {
    if (first.numerator_ * second.numerator_ < 0) {
        if (first.numerator_ > 0) {
            return true;
        }
    }

    if (first.numerator_ * second.denominator_ > second.numerator_ * first.denominator_) {
        return true;
    }
    return false;
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
