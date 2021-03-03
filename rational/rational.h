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
    int numerator;
    int denominator;

    void Reduce();

public:
    Rational();
    Rational(int x);
    Rational(int x, int y);

    int GetNumerator() const;
    int GetDenominator() const;
    void SetNumerator(int num);
    void SetDenominator(int num);

    friend std::istream &operator>>(std::istream &is, const Rational &num);
    friend std::ostream &operator<<(std::ostream &out, const Rational &num);

    Rational &operator+=(Rational add);
    Rational &operator-=(Rational add);
    Rational &operator*=(Rational add);
    Rational &operator/=(Rational add);

    friend bool operator>(const Rational &first, const Rational &second);
};

Rational operator+(Rational first, Rational second);
Rational operator-(Rational first, Rational second);
Rational operator*(Rational first, Rational second);
Rational operator/(Rational first, Rational second);

Rational operator+(Rational num);
Rational operator-(Rational num);

Rational &operator++(Rational &num);
Rational &operator--(Rational &num);
Rational operator++(Rational &num, int);
Rational operator--(Rational &num, int);

bool operator<(const Rational &first, const Rational &second);
bool operator==(const Rational &first, const Rational &second);
bool operator!=(const Rational &first, const Rational &second);
bool operator>=(const Rational &first, const Rational &second);
bool operator<=(const Rational &first, const Rational &second);

#endif