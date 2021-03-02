#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include <iterator>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
public:
    ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
    }
};

template <class T, size_t N>
class Array {
public:
    T arr[N];

    T &At(size_t ind);
    T &Front();
    T &Back();
    T const &Front() const;
    T const &Back() const;

    size_t Size() const;
    T *Data();
    const T *Data() const;
    bool Empty() const;
    void Fill(const T &value);
    void Swap(Array<T, N> &other);

    T &operator[](size_t i);
    const T &operator[](size_t i) const;
};

template <class T, size_t N>
T &Array<T, N>::At(size_t ind) {
    if (ind <= N - 1) {
        return arr[ind];
    }
    throw ArrayOutOfRange{};
}

template <class T, size_t N>
T &Array<T, N>::Front() {
    return arr[0];
}

template <class T, size_t N>
T &Array<T, N>::Back() {
    if (N == 0) {
        return arr[0];
    }
    return arr[N - 1];
}

template <class T, size_t N>
T const &Array<T, N>::Front() const {
    return arr[0];
}

template <class T, size_t N>
T const &Array<T, N>::Back() const {
    if (N == 0) {
        return arr[0];
    }
    return arr[N - 1];
}

template <class T, size_t N>
size_t Array<T, N>::Size() const {
    return N;
}

template <class T, size_t N>
const T *Array<T, N>::Data() const {
    return &arr[0];
}

template <class T, size_t N>
T *Array<T, N>::Data() {
    return &arr[0];
}

template <class T, size_t N>
bool Array<T, N>::Empty() const {
    bool ans = false;
    if (N == 0) {
        ans = true;
    }
    return ans;
}

template <class T, size_t N>
void Array<T, N>::Fill(const T &value) {
    for (size_t i = 0; i < N; ++i) {
        arr[i] = value;
    }
}

template <class T>
void swap(T &num1, T &num2) {  // NOLINT
    T temp = num1;
    num1 = num2;
    num2 = temp;
}

template <class T, size_t N>
void Array<T, N>::Swap(Array<T, N> &other) {
    for (size_t i = 0; i < N; ++i) {
        swap(arr[i], other[i]);
    }
}

template <class T, size_t N>
T &Array<T, N>::operator[](size_t i) {
    return arr[i];
}

template <class T, size_t N>
const T &Array<T, N>::operator[](size_t i) const {
    return arr[i];
}

template <class T1, class T2, size_t N>
bool operator<(const Array<T1, N> &first, const Array<T2, N> &second) {
    bool ans = false;
    for (size_t i = 0; i < N; ++i) {
        if (second[i] < first[i]) {
            break;
        }
        if (first[i] < second[i]) {
            ans = true;
            break;
        }
    }
    return ans;
}

template <class T1, class T2, size_t N>
bool operator>(const Array<T1, N> &first, const Array<T2, N> &second) {
    return (second < first);
}

template <class T1, class T2, size_t N>
bool operator==(const Array<T1, N> &first, const Array<T2, N> &second) {
    return (!(first < second) && !(second < first));
}

template <class T1, class T2, size_t N>
bool operator!=(const Array<T1, N> &first, const Array<T2, N> &second) {
    return !(first == second);
}

template <class T1, class T2, size_t N>
bool operator<=(const Array<T1, N> &first, const Array<T2, N> &second) {
    return (first < second || first == second);
}

template <class T1, class T2, size_t N>
bool operator>=(const Array<T1, N> &first, const Array<T2, N> &second) {
    return (first > second || first == second);
}

namespace std {  // NOLINT
template <class T, size_t N>
void Swap(Array<T, N> &first, Array<T, N> &second) {
    first.Swap(second);
}
}  // namespace std

#endif
