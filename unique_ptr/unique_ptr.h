#ifndef UNIQUE_PTR_UNIQUE_PTR_H
#define UNIQUE_PTR_UNIQUE_PTR_H

#include <iostream>

template <class T>
class UniquePtr {
private:
    T *ptr_;

public:
    UniquePtr();
    explicit UniquePtr(T *ptr);
    UniquePtr(const UniquePtr<T> &other) = delete;
    UniquePtr(UniquePtr<T> &&other) noexcept;

    UniquePtr &operator=(const UniquePtr<T> &other) = delete;
    UniquePtr &operator=(UniquePtr<T> &&other) noexcept;

    ~UniquePtr();

    T *Release();
    void Reset(T *ptr = nullptr) noexcept;
    void Swap(UniquePtr<T> &other);
    T *Get() const;

    T &operator*() const;
    T *operator->() const;
    explicit operator bool() const noexcept;
};

template <class T>
UniquePtr<T>::UniquePtr() : ptr_(nullptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(T *ptr) : ptr_(ptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T> &&other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

template <class T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr<T> &&other) noexcept {
    if (&other == this) {
        return *this;
    }

    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
    delete ptr_;
}

template <class T>
T &UniquePtr<T>::operator*() const {
    return *ptr_;
}

template <class T>
T *UniquePtr<T>::operator->() const {
    return ptr_;
}

template <class T>
T *UniquePtr<T>::Release() {
    T *ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
}

template <class T>
T *UniquePtr<T>::Get() const {
    return ptr_;
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr<T> &other) {
    UniquePtr<T> tmp = std::move(this);
    this = std::move(other);
    other = std::move(tmp);
}

template <class T>
void UniquePtr<T>::Reset(T *ptr) noexcept {
    delete ptr_;
    ptr_ = ptr;
}

template <class T>
UniquePtr<T>::operator bool() const noexcept {
    return !(ptr_ == nullptr);
}

#endif  // UNIQUE_PTR_UNIQUE_PTR_H
