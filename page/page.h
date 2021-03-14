#ifndef DEQUE_PAGE_PAGE_H
#define DEQUE_PAGE_PAGE_H

#include <iostream>

template <class T, size_t N>
class Page {
private:
    T buffer [N];
    bool back;
    bool front;
    size_t size;
public:
    Page();
    Page(const Page &other);

    int status = 0;
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
Page<T, N>::Page() : back(true), front(true), size(0) {
}

template <class T, size_t N>
Page<T, N>::Page(const Page &other) : back(other.IsBack()), front(other.IsFront()), size(other.Size()) {
    status = other.status;
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = other.buffer[i];
    }
}

template <class T, size_t N>
Page<T, N> &Page<T, N>::operator=(const Page<T, N> &other) {
    if (&other != this) {
        back = other.IsBack();
        front = other.IsFront();
        size = other.Size();
        status = other.status;

        for (size_t i = 0; i < size; ++i) {
            buffer[i] = other.buffer[i];
        }
    }
    return *this;
}

template <class T, size_t N>
void Page<T, N>::Clear() {
    size = 0;
    front = back = true;
}

template <class T, size_t N>
size_t Page<T, N>::Size() const {
    return size;
}

template <class T, size_t N>
T &Page<T, N>::operator[](size_t ind) {
    if (front == true) {
        return buffer[size - ind - 1];
    }
    return buffer[ind];
}

template <class T, size_t N>
const T &Page<T, N>::operator[](size_t ind) const {
    if (front == true || status == 1) {
        return buffer[size - ind - 1];
    }
    return buffer[ind];
}

template <class T, size_t N>
T &Page<T, N>::Front() {
    if (back == true || status == 1) {
        return buffer[0];
    }
    if (size == 0) {
        return buffer[0];
    }
    return buffer[size - 1];
}

template <class T, size_t N>
const T &Page<T, N>::Front() const {
    if (back == true) {
        return buffer[0];
    }
    if (size == 0) {
        return buffer[0];
    }
    return buffer[size - 1];
}

template <class T, size_t N>
T &Page<T, N>::Back() {
    if (back == true) {
        if (size == 0) {
            return buffer[0];
        }
        return buffer[size - 1];
    }
    return buffer[0];
}

template <class T, size_t N>
const T &Page<T, N>::Back() const {
    if (back == true) {
        if (size == 0) {
            return buffer[0];
        }
        return buffer[size - 1];
    }
    return buffer[0];
}

template <class T, size_t N>
bool Page<T, N>::Empty() const {
    return (size == 0);
}

template <class T, size_t N>
bool Page<T, N>::Full() const {
    return (size == N);
}

template <class T, size_t N>
bool Page<T, N>::IsFront() const {
    return front;
}

template <class T, size_t N>
bool Page<T, N>::IsBack() const {
    return back;
}

template <class T, size_t N>
void Page<T, N>::PushBack(const T &value) {
    front = false;
    if (size < N) {
        buffer[size] = value;
        ++size;
    }
    if (size == N) {
        back = false;
        status = 2;
    }

}

template <class T, size_t N>
void Page<T, N>::PopBack() {
    if (size == N) {
        back = true;
        status = 0;
    }
    --size;
    if (size == 0) {
        front = back = true;
    }
}

template <class T, size_t N>
void Page<T, N>::PushFront(const T &value) {
    back = false;
    if (size < N) {
        buffer[size] = value;
        ++size;
    }
    if (size == N) {
        front = false;
        status = 1;
    }
}

template <class T, size_t N>
void Page<T, N>::PopFront() {
    if (size == N) {
        front = true;
        status = 0;
    }

    --size;

    if (size == 0) {
        front = back = true;
    }
}

#endif  // DEQUE_PAGE_PAGE_H

