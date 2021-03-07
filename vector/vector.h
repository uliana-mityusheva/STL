#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>

class VectorOutOfRange : public std::out_of_range {
public:
    VectorOutOfRange() : std::out_of_range("VectorOutOfRange") {
    }
};

template <class T>
class Vector {
private:
    T *buffer_;
    size_t size_;
    size_t capacity_;

    void Fill(size_t start, size_t end, const T &value);
    size_t FindCorrectionCapacity();
    void BufferReallocation(size_t new_capacity);  // new_capacity can be less then size
public:
    Vector();
    explicit Vector(size_t size);
    Vector(size_t size, const T &value);
    Vector(const Vector &other);
    ~Vector();

    void Clear();
    void Swap(Vector<T> &other);
    void PushBack(const T &value);
    void PopBack();
    void Resize(size_t new_size);
    void Resize(size_t new_size, const T &value);
    void Reserve(size_t new_cap);
    void ShrinkToFit();

    T &At(size_t ind);
    const T &At(size_t ind) const;
    T &Front();
    const T &Front() const;
    T &Back();
    const T &Back() const;
    bool Empty() const;
    size_t Size() const;
    size_t Capacity() const;
    T *Data();
    const T *Data() const;

    T &operator[](size_t ind);
    const T &operator[](size_t ind) const;

    Vector &operator=(const Vector &other);  // if &other == this return *this -> for(..) + delete old buffer
};

template <class T>
void Copy(T *buffer_to, T *buffer_from, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        buffer_to[i] = buffer_from[i];
    }
}

template <class T>
void Vector<T>::Fill(size_t start, size_t end, const T &value) {
    for (size_t i = start; i < end; ++i) {
        buffer_[i] = value;
    }
}

template <class T>
size_t Vector<T>::FindCorrectionCapacity() {
    return (capacity_ == 0) ? 1 : capacity_ * 2;
}

template <class T>
void Vector<T>::BufferReallocation(size_t new_capacity) {
    T *new_buffer = (new_capacity == 0) ? nullptr : new T[new_capacity];
    size_ = std::min(size_, new_capacity);

    Copy(new_buffer, buffer_, size_);
    capacity_ = new_capacity;
    delete[] buffer_;
    buffer_ = new_buffer;
}

template <class T>
Vector<T>::Vector() : buffer_(nullptr), size_(0), capacity_(0) {
}

template <class T>
Vector<T>::Vector(size_t size) : size_(size), capacity_(FindCorrectionCapacity(size_)) {
    buffer_ = new T[capacity_];
}

template <class T>
Vector<T>::Vector(size_t size, const T &value) : size_(size), capacity_(FindCorrectionCapacity(size_)) {
    buffer_ = new T[capacity_];
    Fill(0, size_, value);
}

template <class T>
Vector<T>::Vector(const Vector &other) : size_(other.Size()), capacity_(other.Capacity()) {
    buffer_ = new T[capacity_];
    Copy(buffer_, other.buffer_, size_);
}

template <class T>
Vector<T>::~Vector() {
    delete[] buffer_;
}

template <class T>
void Vector<T>::Clear() {
    size_ = 0;
}

template <class T>
void Swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

template <class T>
void Vector<T>::Swap(Vector<T> &other) {
    ::Swap(buffer_, other.buffer_);  // use global Swap
    ::Swap(capacity_, other.capacity_);
    ::Swap(size_, other.size_);
}

template <class T>
void Vector<T>::PushBack(const T &value) {
    if (size_ == capacity_) {
        capacity_ = FindCorrectionCapacity();
        BufferReallocation(capacity_);
    }
    buffer_[size_] = value;
    ++size_;
}

template <class T>
void Vector<T>::PopBack() {
    if (size_ > 0) {
        --size_;
    }  // realoc + change capacity
}

template <class T>
void Vector<T>::Resize(size_t new_size) {
    if (new_size > capacity_) {
        BufferReallocation(new_size);
    }
    size_ = new_size;
}

template <class T>
void Vector<T>::Resize(size_t new_size, const T &value) {
    if (new_size > size_) {
        if (new_size > capacity_) {
            BufferReallocation(new_size);
        }
        Fill(size_, new_size, value);
    }
    size_ = new_size;
}

template <class T>
void Vector<T>::Reserve(size_t new_cap) {
    if (new_cap > capacity_) {
        BufferReallocation(new_cap);
    }
}

template <class T>
void Vector<T>::ShrinkToFit() {
    if (size_ != capacity_) {
        BufferReallocation(size_);
    }
}

template <class T>
T &Vector<T>::operator[](size_t ind) {
    return buffer_[ind];
}

template <class T>
const T &Vector<T>::operator[](size_t ind) const {
    return buffer_[ind];
}

template <class T>
T &Vector<T>::At(size_t ind) {
    if (ind < size_) {
        return buffer_[ind];
    }
    throw VectorOutOfRange{};
}

template <class T>
const T &Vector<T>::At(size_t ind) const {
    if (ind < size_) {
        return buffer_[ind];
    }
    throw VectorOutOfRange{};
}

template <class T>
T &Vector<T>::Front() {
    return buffer_[0];
}

template <class T>
const T &Vector<T>::Front() const {
    return buffer_[0];
}

template <class T>
T &Vector<T>::Back() {
    if (size_ == 0) {
        return buffer_[0];
    }
    return buffer_[size_ - 1];
}

template <class T>
const T &Vector<T>::Back() const {
    if (size_ == 0) {
        return buffer_[0];
    }
    return buffer_[size_ - 1];
}

template <class T>
bool Vector<T>::Empty() const {
    return (size_ == 0);
}

template <class T>
size_t Vector<T>::Size() const {
    return size_;
}

template <class T>
size_t Vector<T>::Capacity() const {
    return capacity_;
}

template <class T>
const T *Vector<T>::Data() const {
    return &buffer_[0];
}

template <class T>
T *Vector<T>::Data() {
    return &buffer_[0];
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (&other != this) {
        delete[] buffer_;
        buffer_ = new T[other.capacity_];
        size_ = other.size_;
        Copy(buffer_, other.buffer_, size_);
    }
    return *this;
}

template <class T1, class T2>
bool operator<(const Vector<T1> &first, const Vector<T2> &second) {
    bool ans = false;
    size_t i = 0;

    if (first.Size() < second.Size()) {
        ans = true;
    }

    for (i = 0; i < first.Size() && i < second.Size(); ++i) {
        if (second[i] < first[i]) {
            ans = false;
            break;
        }
        if (first[i] < second[i]) {
            ans = true;
            break;
        }
    }
    return ans;
}

template <class T1, class T2>
bool operator>(const Vector<T1> &first, const Vector<T2> &second) {
    return (second < first);
}

template <class T1, class T2>
bool operator==(const Vector<T1> &first, const Vector<T2> &second) {
    return (!(first < second) && !(second < first));
}

template <class T1, class T2>
bool operator!=(const Vector<T1> &first, const Vector<T2> &second) {
    return !(first == second);
}

template <class T1, class T2>
bool operator<=(const Vector<T1> &first, const Vector<T2> &second) {
    return (first < second || first == second);
}

template <class T1, class T2>
bool operator>=(const Vector<T1> &first, const Vector<T2> &second) {
    return (first > second || first == second);
}

#endif  // VECTOR_VECTOR_H