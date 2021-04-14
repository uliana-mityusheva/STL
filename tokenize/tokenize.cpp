#include "tokenize.h"
#include <stdlib.h>
#include <variant>

std::vector<Token> Tokenize(const std::string &input) {
    std::vector<Token> ans;
    size_t size = input.size();
    for (size_t i = 0; i < size; ++i) {
        if (input[i] == ' ') {
            continue;
        }

        if (input[i] == '(') {
            OpeningBracketToken open_bracket;
            ans.emplace_back(open_bracket);
            continue;
        }

        if (input[i] == ')') {
            ClosingBracketToken close_bracket;
            ans.emplace_back(close_bracket);
            continue;
        }

        if (input[i] == '+') {
            if (i < size - 1 && isdigit(input[i + 1])) {
                NumberToken number;
                number.value = std::atoi(&input[i]);
                while (isdigit(input[i + 1])) {
                    ++i;
                }
                ans.emplace_back(number);
                continue;
            } else if (input[i + 1] == ' ' || i + 1 == size) {
                PlusToken plus;
                ans.emplace_back(plus);
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
                ans.emplace_back(number);
                continue;
            } else if (input[i + 1] == ' ' || i + 1 == size) {
                MinusToken minus;
                ans.emplace_back(minus);
                continue;
            }
        }

        if ((input[i] == '*' && input[i + 1] == ' ') || i + 1 == size) {
            MultiplyToken multiply;
            ans.emplace_back(multiply);
            continue;
        }

        if ((input[i] == '/' && input[i + 1] == ' ') || i + 1 == size) {
            DivideToken divide;
            ans.emplace_back(divide);
            continue;
        }

        if ((input[i] == '%' && input[i + 1] == ' ') || i + 1 == size) {
            ResidualToken residual;
            ans.emplace_back(residual);
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
                ans.emplace_back(number);
                i = j - 1;
                continue;
            }
        }

        if (i <= size - 4 && input[i] == 's' && input[i + 1] == 'q' && input[i + 2] == 'r' && input[i + 3] == ' ') {
            i += 2;
            SqrToken sqr;
            ans.emplace_back(sqr);
        } else if (i <= size - 4 && input[i] == 'm' && input[i + 1] == 'a' && input[i + 2] == 'x' &&
                   input[i + 3] == ' ') {
            i += 2;
            MaxToken max;
            ans.emplace_back(max);
        } else if (i <= size - 4 && input[i] == 'm' && input[i + 1] == 'i' && input[i + 2] == 'n' &&
                   input[i + 3] == ' ') {
            i += 2;
            MinToken min;
            ans.emplace_back(min);
        } else if (i <= size - 4 && input[i] == 'a' && input[i + 1] == 'b' && input[i + 2] == 's' &&
                   input[i + 3] == ' ') {
            i += 2;
            AbsToken abs;
            ans.emplace_back(abs);
        } else {
            std::string str = {};
            while (i < size && input[i] != ' ') {
                str += input[i];
                ++i;
            }
            UnknownToken unknown;
            unknown.value = str;
            ans.emplace_back(unknown);
            --i;
        }
    }
    return ans;
}
