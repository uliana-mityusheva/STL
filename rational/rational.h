#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

#include <iostream>
#include <numeric>
#include <cstdlib>

class RationalDivisionByZero : public std::runtime_error {
public:
    RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
    }
};

class Rational {
private:
    int numerator_;
    int denominator_;

    void Reduce();

public:
    Rational();
    Rational(int num);
    Rational(int num, int den);

    int GetNumerator() const;
    int GetDenominator() const;
    void SetNumerator(int fract);
    void SetDenominator(int fract);

    friend std::istream &operator>>(std::istream &is, Rational &fract);
    friend std::ostream &operator<<(std::ostream &out, const Rational &fract);

    Rational &operator+=(Rational other);
    Rational &operator-=(Rational other);
    Rational &operator*=(Rational other);
    Rational &operator/=(Rational other);

    friend bool operator>(const Rational &first, const Rational &second);
};

Rational operator+(Rational first, Rational second);
Rational operator-(Rational first, Rational second);
Rational operator*(Rational first, Rational second);
Rational operator/(Rational first, Rational second);

Rational operator+(Rational fract);
Rational operator-(Rational fract);

Rational &operator++(Rational &fract);
Rational &operator--(Rational &fract);
Rational operator++(Rational &fract, int);
Rational operator--(Rational &fract, int);

bool operator<(const Rational &first, const Rational &second);
bool operator==(const Rational &first, const Rational &second);
bool operator!=(const Rational &first, const Rational &second);
bool operator>=(const Rational &first, const Rational &second);
bool operator<=(const Rational &first, const Rational &second);

#endif