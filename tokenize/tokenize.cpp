#include <variant>
#include <stdlib.h>

#include "tokenize.h"

std::vector<Token> Tokenize(const std::string &input) {
    std::vector<Token> token;
    size_t size = input.size();
    for (size_t i = 0; i < size; ++i) {
        if (input[i] == ' ') {
            continue;
        }

        if (input[i] == '(') {
            OpeningBracketToken open_bracket;
            token.emplace_back(open_bracket);
            continue;
        }

        if (input[i] == ')') {
            ClosingBracketToken close_bracket;
            token.emplace_back(close_bracket);
            continue;
        }

        if (input[i] == '+') {
            if (i < size - 1 && isdigit(input[i + 1])) {
                NumberToken number;
                number.value = std::atoi(&input[i]);
                while (isdigit(input[i + 1])) {
                    ++i;
                }
                token.emplace_back(number);
                continue;
            } else if (input[i + 1] == ' ' || i + 1 == size) {
                PlusToken plus;
                token.emplace_back(plus);
                continue;
            }
        }

        if (input[i] == '-') {
            if (i < size - 1 && isdigit(input[i + 1])) {
                NumberToken number;
                number.value = std::atoi(&input[i]);
                while (isdigit(input[i + 1])) {
                    ++i;
                }
                token.emplace_back(number);
                continue;
            } else if (input[i + 1] == ' ' || i + 1 == size) {
                MinusToken minus;
                token.emplace_back(minus);
                continue;
            }
        }

        if ((input[i] == '*' && input[i + 1] == ' ') || i + 1 == size) {
            MultiplyToken multiply;
            token.emplace_back(multiply);
            continue;
        }

        if ((input[i] == '/' && input[i + 1] == ' ') || i + 1 == size) {
            DivideToken divide;
            token.emplace_back(divide);
            continue;
        }

        if ((input[i] == '%' && input[i + 1] == ' ') || i + 1 == size) {
            ResidualToken residual;
            token.emplace_back(residual);
            continue;
        }

        if (isdigit(input[i])) {
            NumberToken number;
            number.value = std::atoi(&input[i]);
            size_t j = i;
            while (isdigit(input[j])) {
                ++j;
            }

            if (input[j] == ' ' || j == size) {
                token.emplace_back(number);
                i = j - 1;
                continue;
            }
        }

        if (i <= size - 4 && input[i] == 's' && input[i + 1] == 'q' && input[i + 2] == 'r' && input[i + 3] == ' ') {
            i += 2;
            SqrToken sqr;
            token.emplace_back(sqr);
        } else if (i <= size - 4 && input[i] == 'm' && input[i + 1] == 'a' && input[i + 2] == 'x' &&
                   input[i + 3] == ' ') {
            i += 2;
            MaxToken max;
            token.emplace_back(max);
        } else if (i <= size - 4 && input[i] == 'm' && input[i + 1] == 'i' && input[i + 2] == 'n' &&
                   input[i + 3] == ' ') {
            i += 2;
            MinToken min;
            token.emplace_back(min);
        } else if (i <= size - 4 && input[i] == 'a' && input[i + 1] == 'b' && input[i + 2] == 's' &&
                   input[i + 3] == ' ') {
            i += 2;
            AbsToken abs;
            token.emplace_back(abs);
        } else {
            std::string str = {};
            while (i < size && input[i] != ' ') {
                str += input[i];
                ++i;
            }
            UnknownToken unknown;
            unknown.value = str;
            token.emplace_back(unknown);
            --i;
        }
    }
    return token;
}

bool PlusToken::operator==(const PlusToken &) const {
    return true;
}

bool MinusToken::operator==(const MinusToken &) const {
    return true;
}

bool MinToken::operator==(const MinToken &) const {
    return true;
}

bool MaxToken::operator==(const MaxToken &) const {
    return true;
}

bool DivideToken::operator==(const DivideToken &) const {
    return true;
}

bool AbsToken::operator==(const AbsToken &) const {
    return true;
}

bool MultiplyToken::operator==(const MultiplyToken &) const {
    return true;
}

bool ResidualToken::operator==(const ResidualToken &) const {
    return true;
}

bool OpeningBracketToken::operator==(const OpeningBracketToken &) const {
    return true;
}

bool ClosingBracketToken::operator==(const ClosingBracketToken &) const {
    return true;
}

bool SqrToken::operator==(const SqrToken &) const {
    return true;
}

bool NumberToken::operator==(const NumberToken &other) const {
    return (other.value == value);
}

bool UnknownToken::operator==(const UnknownToken &) const {
    return true;
}