#ifndef DEQUE_PAGE_PAGE_H
#define DEQUE_PAGE_PAGE_H

#include <iostream>

template <class T, size_t N>
class Page {
private:
    T buffer_[N];
    bool back_;
    bool front_;
    size_t size_;
    int status_;

public:
    Page();
    Page(const Page &other);

    T &Front();
    const T &Front() const;
    T &Back();
    const T &Back() const;

    bool Empty() const;
    bool Full() const;
    bool IsBack() const;
    bool IsFront() const;

    size_t Size() const;

    void PushBack(const T &value);
    void PopBack();
    void PushFront(const T &value);
    void PopFront();

    void Clear();

    T &operator[](size_t ind);
    const T &operator[](size_t ind) const;

    Page &operator=(const Page &other);
};

template <class T, size_t N>
Page<T, N>::Page() : back_(true), front_(true), size_(0), status_(0) {
}

template <class T, size_t N>
Page<T, N>::Page(const Page &other) : back_(other.IsBack()), front_(other.IsFront()), size_(other.Size()) {
    status_ = other.status_;
    for (size_t i = 0; i < size_; ++i) {
        buffer_[i] = other.buffer_[i];
    }
}

template <class T, size_t N>
Page<T, N> &Page<T, N>::operator=(const Page<T, N> &other) {
    if (&other != this) {
        back_ = other.IsBack();
        front_ = other.IsFront();
        size_ = other.Size();
        status_ = other.status_;

        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] = other.buffer_[i];
        }
    }
    return *this;
}

template <class T, size_t N>
void Page<T, N>::Clear() {
    size_ = 0;
    front_ = back_ = true;
}

template <class T, size_t N>
size_t Page<T, N>::Size() const {
    return size_;
}

template <class T, size_t N>
T &Page<T, N>::operator[](size_t ind) {
    if (front_) {
        return buffer_[size_ - ind - 1];
    }
    return buffer_[ind];
}

template <class T, size_t N>
const T &Page<T, N>::operator[](size_t ind) const {
    if (front_ || status_ == 1) {
        return buffer_[size_ - ind - 1];
    }
    return buffer_[ind];
}

template <class T, size_t N>
T &Page<T, N>::Front() {
    if (back_ || status_ == 1) {
        return buffer_[0];
    }
    if (size_ == 0) {
        return buffer_[0];
    }
    return buffer_[size_ - 1];
}

template <class T, size_t N>
const T &Page<T, N>::Front() const {
    if (back_) {
        return buffer_[0];
    }
    if (size_ == 0) {
        return buffer_[0];
    }
    return buffer_[size_ - 1];
}

template <class T, size_t N>
T &Page<T, N>::Back() {
    if (back_) {
        if (size_ == 0) {
            return buffer_[0];
        }
        return buffer_[size_ - 1];
    }
    return buffer_[0];
}

template <class T, size_t N>
const T &Page<T, N>::Back() const {
    if (back_) {
        if (size_ == 0) {
            return buffer_[0];
        }
        return buffer_[size_ - 1];
    }
    return buffer_[0];
}

template <class T, size_t N>
bool Page<T, N>::Empty() const {
    return (size_ == 0);
}

template <class T, size_t N>
bool Page<T, N>::Full() const {
    return (size_ == N);
}

template <class T, size_t N>
bool Page<T, N>::IsFront() const {
    return front_;
}

template <class T, size_t N>
bool Page<T, N>::IsBack() const {
    return back_;
}

template <class T, size_t N>
void Page<T, N>::PushBack(const T &value) {
    front_ = false;
    if (size_ < N) {
        buffer_[size_] = value;
        ++size_;
    }
    if (size_ == N) {
        back_ = false;
        status_ = 2;
    }
}

template <class T, size_t N>
void Page<T, N>::PopBack() {
    if (size_ == N) {
        back_ = true;
        status_ = 0;
    }
    --size_;
    if (size_ == 0) {
        front_ = back_ = true;
    }
}

template <class T, size_t N>
void Page<T, N>::PushFront(const T &value) {
    back_ = false;
    if (size_ < N) {
        buffer_[size_] = value;
        ++size_;
    }
    if (size_ == N) {
        front_ = false;
        status_ = 1;
    }
}

template <class T, size_t N>
void Page<T, N>::PopFront() {
    if (size_ == N) {
        front_ = true;
        status_ = 0;
    }

    --size_;

    if (size_ == 0) {
        front_ = back_ = true;
    }
}

#endif  // DEQUE_PAGE_PAGE_H
