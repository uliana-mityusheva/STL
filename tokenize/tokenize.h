#ifndef CALCULATOR_TOKENIZE_H
#define CALCULATOR_TOKENIZE_H

#include <iostream>
#include <variant>
#include <vector>

struct PlusToken {
    bool operator==(const PlusToken &) const {
        return true;
    }
};

struct MinusToken {
    bool operator==(const MinusToken &) const {
        return true;
    }
};

struct MultiplyToken {
    bool operator==(const MultiplyToken &) const {
        return true;
    }
};

struct DivideToken {
    bool operator==(const DivideToken &) const {
        return true;
    }
};

struct ResidualToken {
    bool operator==(const ResidualToken &) const {
        return true;
    }
};

struct OpeningBracketToken {
    bool operator==(const OpeningBracketToken &) const {
        return true;
    }
};

struct ClosingBracketToken {
    bool operator==(const ClosingBracketToken &) const {
        return true;
    }
};

struct SqrToken {
    bool operator==(const SqrToken &) const {
        return true;
    }
};

struct MaxToken {
    bool operator==(const MaxToken &) const {
        return true;
    }
};

struct MinToken {
    bool operator==(const MinToken &) const {
        return true;
    }
};

struct AbsToken {
    bool operator==(const AbsToken &) const {
        return true;
    }
};

struct NumberToken {
    int value;
    bool operator==(const NumberToken &other) const {
        return (other.value == value);
    }
};

struct UnknownToken {
    std::string value;
    bool operator==(const UnknownToken &) const {
        return true;
    }
};

using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
                           ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

std::vector<Token> Tokenize(const std::string &input);

#endif  // CALCULATOR_TOKENIZE_H
