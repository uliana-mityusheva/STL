#ifndef MATRIX_ARRAY_MATRIX_ARRAY_H
#define MATRIX_ARRAY_MATRIX_ARRAY_H

#include <util/constants.h>
#include <iostream>

class MatrixArrayIsDegenerateError : public std::runtime_error {
public:
    MatrixArrayIsDegenerateError() : std::runtime_error("MatrixArrayIsDegenerateError") {
    }
};

class MatrixArrayOutOfRange : public std::out_of_range {
public:
    MatrixArrayOutOfRange() : std::out_of_range("MatrixArrayOutOfRange") {
    }
};

template <class T, size_t N, size_t M>
struct MatrixArray {
public:
    T matrix[N][M];

    MatrixArray<T, 1, 1> &OneElementMatrix (const T &num);
    size_t RowsNumber() const;
    size_t ColumnsNumber() const;
    T &At (size_t string, size_t column);
    T At (size_t string, size_t column) const;
    MatrixArray<T, M, N> GetTransposed() const;

    T operator()(size_t string, size_t column) const;
    T &operator()(size_t string, size_t column);

    //friend std::istream& operator>>(std::istream& is, MatrixArray &num);
    //friend std::ostream& operator<<(std::ostream& out, MatrixArray &num);

    MatrixArray &operator*=(const int &num);
    MatrixArray &operator/=(const int &num);
};

template <class T, size_t N, size_t M>
size_t MatrixArray<T, N, M>::RowsNumber() const {
    return N;
}

template <class T, size_t N, size_t M>
size_t MatrixArray<T, N, M>::ColumnsNumber() const {
    return M;
}

template<class T, size_t N, size_t M>
T &MatrixArray<T, N, M>::At (size_t string, size_t column) {
    if (string < N && column < M) {
        return matrix[string][column];
    }
    throw MatrixArrayOutOfRange{};
}

template<class T, size_t N, size_t M>
T MatrixArray<T, N, M>::At (size_t string, size_t column) const {
    if (string < N && column < M) {
        return matrix[string][column];
    }
    throw MatrixArrayOutOfRange{};
}

template <class T, size_t N, size_t M>
MatrixArray<T, M, N> MatrixArray<T, N, M>::GetTransposed() const {
    MatrixArray<T, M, N> new_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            new_matrix.matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}

template<class T, size_t N, size_t M>
T MatrixArray<T, N, M>::operator()(size_t string, size_t column) const {
    return matrix[string][column];
}

template<class T, size_t N, size_t M>
T &MatrixArray<T, N, M>::operator()(size_t string, size_t column) {
    return matrix[string][column];
}

template <class T, size_t N, size_t M>
std::istream &operator>>(std::istream &is, MatrixArray<T, N, M> &matrix) {
    for(size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            is >> matrix(i, j);
        }
    }
    return is;
}

template<class T, size_t N, size_t M>
std::ostream &operator<<(std::ostream &os, const MatrixArray<T, N, M> &matrix) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M - 1; ++j) {
            os << matrix(i, j) << " ";
        }
        os << matrix(i, M - 1) << "\n";
    }
    return os;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M> &operator+=(MatrixArray<T, N, M> &first, const MatrixArray<T, N, M> &second) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            first(i, j) += second(i, j);
        }
    }
    return first;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M> &operator-=(MatrixArray<T, N, M> &first, const MatrixArray<T, N, M> &second) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            first(i, j) -= second(i, j);
        }
    }
    return first;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M>operator+(const MatrixArray<T, N, M> &first, const MatrixArray<T, N, M> &second) {
    MatrixArray<T, N, M> copy = first;
    return copy += second;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M>operator-(const MatrixArray<T, N, M> &first, const MatrixArray<T, N, M> &second) {
    MatrixArray<T, N, M> copy = first;
    return copy -= second;
}

template <class T, size_t N, size_t M, size_t P>
MatrixArray<T, N, P>operator*(const MatrixArray<T, N, M> &first, const MatrixArray<T, M, P> &second) {
    MatrixArray<T, N, P> ans;

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < P; ++j) {
            ans(i, j) = kZero<T>;
        }
    }

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < P; ++j) {
            for (size_t k = 0; k < M; ++k) {
                ans(i, j) += first(i, k) * second(k, j);
            }
        }
    }
    return ans;
}

template <class T, size_t N, size_t M>
MatrixArray<T, M, N> &operator*=(MatrixArray<T, M, N> &first, const MatrixArray<T, N, N> &second) {
    first = first * second;
    return first;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M> &MatrixArray<T, N, M>::operator*=(const int &num) { //проверить
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            (*this)(i, j) *= num;
        }
    }
    return *this;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M> &MatrixArray<T, N, M>::operator/=(const int &num) { //проверить
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            (*this)(i, j) /= num;
        }
    }
    return *this;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M> operator*(const MatrixArray<T, N, M> &matrix, const int &num) { // матрица на число
    MatrixArray<T, N, M> copy = matrix;
    return copy *= num;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M> operator*(const int &num, const MatrixArray<T, N, M> &matrix) { // число на матрицу
    return matrix * num;
}

template <class T, size_t N, size_t M>
MatrixArray<T, N, M> operator/(const MatrixArray<T, N, M> &matrix, const int &num) {
    MatrixArray<T, N, M> copy = matrix;
    return copy /= num;
}

template <class T, size_t N, size_t M>
bool operator==(const MatrixArray<T, N, M> &first, const MatrixArray<T, N, M> &second) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (first(i, j) != second(i, j)) {
                return false;
            }
        }
    }
    return true;
}

template <class T, size_t N, size_t M>
bool operator!=(const MatrixArray<T, N, M> &first, const MatrixArray<T, N, M> &second) {
    return !(first == second);
}

#endif