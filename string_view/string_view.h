#ifndef STRING_VIEW_STRING_VIEW_H
#define STRING_VIEW_STRING_VIEW_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <cstring>

class StringView {
private:
    const char *str_;
    size_t size_;

public:
    StringView();
    StringView(const char *other);  // NOLINT
    StringView(const char *other, size_t size);

    StringView &operator=(const char *other);
    const char &operator[](const size_t &ind) const;
    const char &At(const size_t &ind) const;

    const char &Front() const;
    const char &Back() const;
    size_t Size() const;
    size_t Length() const;
    bool Empty() const;
    const char *Data() const;

    void Swap(StringView &);

    void RemovePrefix(size_t prefix_size);
    void RemoveSuffix(size_t suffix_size);

    StringView Substr(size_t pos, size_t count = -1) const;

    const char *begin();                            // NOLINT
    const char *cbegin();                           // NOLINT
    std::reverse_iterator<const char *> rbegin();   // NOLINT
    std::reverse_iterator<const char *> crbegin();  // NOLINT

    const char *end();                            // NOLINT
    const char *cend();                           // NOLINT
    std::reverse_iterator<const char *> rend();   // NOLINT
    std::reverse_iterator<const char *> crend();  // NOLINT

    using SizeType = size_t;
    using ValueType = char;
    using Iterator = const char *;
    using ConstIterator = const char *;
    using Pointer = char *;
    using ConstPointer = const char *;
    using Reference = char &;
    using DifferenceType = const char;
    using ConstReference = const char &;
    using ConstReverseIterator = std::reverse_iterator<const char *>;
    using ReverseIterator = std::reverse_iterator<const char *>;
};

inline StringView::StringView() : str_(nullptr), size_(0) {
}

inline StringView::StringView(const char *other) : str_(other) {
    size_ = strlen(str_);
}

inline StringView::StringView(const char *other, size_t size) : str_(other), size_(size) {
}

inline StringView &StringView::operator=(const char *other) {
    str_ = other;
    size_ = strlen(other);
    return *this;
}

inline const char &StringView::operator[](const size_t &ind) const {
    return *(str_ + ind);
}

inline const char &StringView::At(const size_t &ind) const {
    if (ind < size_) {
        return *(str_ + ind);
    }
    throw std::out_of_range("");
}

inline bool StringView::Empty() const {
    return size_ == 0;
}

inline const char *StringView::Data() const {
    return str_;
}

inline size_t StringView::Size() const {
    return size_;
}

inline size_t StringView::Length() const {
    return size_;
}

inline const char &StringView::Front() const {
    return *str_;
}

inline const char &StringView::Back() const {
    return *(str_ + size_ - 1);
}

inline void StringView::Swap(StringView &other) {
    std::swap(str_, other.str_);
    std::swap(size_, other.size_);
}

inline void StringView::RemovePrefix(size_t prefix_size) {
    size_ -= prefix_size;
    str_ += prefix_size;
}

inline void StringView::RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
}

inline StringView StringView::Substr(size_t pos, size_t count) const {
    if (pos < size_) {
        const char *str = str_ + pos;
        size_t size = std::min(count, Size() - pos);
        StringView substr(str, size);
        return substr;
    }
    throw std::out_of_range("");
}

inline const char *StringView::begin() {  // NOLINT
    return str_;
}

inline const char *StringView::cbegin() {  // NOLINT
    return str_;
}

inline const char *StringView::end() {  // NOLINT
    return str_ + size_;
}

inline const char *StringView::cend() {  // NOLINT
    return str_ + size_;
}

inline std::reverse_iterator<const char *> StringView::rbegin() {  // NOLINT
    std::reverse_iterator<Iterator> it(end());
    return it;
}

inline std::reverse_iterator<const char *> StringView::rend() {  // NOLINT
    std::reverse_iterator<Iterator> it(begin());
    return it;
}

inline std::reverse_iterator<const char *> StringView::crbegin() {  // NOLINT
    std::reverse_iterator<Iterator> it(end());
    return it;
}

inline std::reverse_iterator<const char *> StringView::crend() {  // NOLINT
    std::reverse_iterator<Iterator> it(begin());
    return it;
}

#endif  // STRING_VIEW_STRING_VIEW_H
