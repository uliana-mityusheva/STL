#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include <iostream>

class BadOptionalAccess {};

template <class T>
class Optional {
private:
    bool is_alive_;
    char memory_[sizeof(T)];
    T *ptr_;

public:
    Optional();
    Optional(const Optional<T> &other);
    Optional(Optional<T> &&other) noexcept;
    explicit Optional(const T &value);
    explicit Optional(T &&value) noexcept;
    ~Optional();

    Optional<T> &operator=(const Optional<T> &other);
    Optional<T> &operator=(Optional<T> &&other) noexcept;
    Optional<T> &operator=(const T &value);
    Optional<T> &operator=(T &&value) noexcept;

    bool HasValue() const;
    explicit operator bool() const noexcept;

    T &Value();
    T const &Value() const;
    T ValueOr(T alternative) const;

    T &operator*();
    T const &operator*() const;

    T *operator->();
    T const *operator->() const;

    template <class... Args>
    T &Emplace(Args... args);

    void Swap(Optional<T> &other);
    void Reset();
};

template <class T>
Optional<T>::Optional() : is_alive_(false) {
    ptr_ = nullptr;
}

template <class T>
Optional<T>::Optional(const Optional<T> &other) : is_alive_(other.is_alive_) {
    if (other.is_alive_) {
        ptr_ = new (&memory_) T(*other.ptr_);
    } else {
        ptr_ = nullptr;
    }
}

template <class T>
Optional<T>::Optional(Optional<T> &&other) noexcept : is_alive_(other.is_alive_) {
    if (other.is_alive_) {
        ptr_ = new (&memory_) T(*other.ptr_);
    } else {
        ptr_ = nullptr;
    }
    other.ptr_ = nullptr;
}

template <class T>
Optional<T>::Optional(const T &value) : is_alive_(true) {
    ptr_ = new (&memory_) T(value);
}

template <class T>
Optional<T>::Optional(T &&value) noexcept : is_alive_(true) {
    ptr_ = new (&memory_) T(value);
}

template <class T>
Optional<T>::~Optional() {
    if (is_alive_) {
        is_alive_ = false;
        ptr_->~T();
    }
}

template <class T>
Optional<T> &Optional<T>::operator=(const Optional<T> &other) {
    if (is_alive_ && !other.is_alive_) {
        is_alive_ = false;
        ptr_->~T();
    } else if (other.is_alive_) {
        if (is_alive_) {
            ptr_ = other.ptr_;
        } else {
            ptr_ = new (&memory_) T(*other.ptr_);
        }
        is_alive_ = true;
    }
    return *this;
}

template <class T>
Optional<T> &Optional<T>::operator=(Optional<T> &&other) noexcept {
    if (is_alive_ && !other.is_alive_) {
        is_alive_ = false;
        ptr_->~T();
    } else if (other.is_alive_) {
        if (is_alive_) {
            ptr_->~T();
        }
        is_alive_ = true;
        ptr_ = new (&memory_) T(*other.ptr_);
        other.ptr_ = nullptr;
    }
    return *this;
}

template <class T>
Optional<T> &Optional<T>::operator=(const T &value) {
    if (is_alive_) {
        *ptr_ = value;
    } else {
        is_alive_ = true;
        ptr_ = new (&memory_) T(value);
    };
    return *this;
}

template <class T>
Optional<T> &Optional<T>::operator=(T &&value) noexcept {
    if (is_alive_) {
        *ptr_ = value;
    } else {
        is_alive_ = true;
        ptr_ = new (&memory_) T(value);
    };
    value = T();
    return *this;
}

template <class T>
bool Optional<T>::HasValue() const {
    return is_alive_;
}

template <class T>
Optional<T>::operator bool() const noexcept {
    return is_alive_;
}

template <class T>
const T &Optional<T>::Value() const {
    if (is_alive_) {
        return *ptr_;
    }
    throw BadOptionalAccess{};
}

template <class T>
T &Optional<T>::Value() {
    if (is_alive_) {
        return *ptr_;
    }
    throw BadOptionalAccess{};
}

template <class T>
T Optional<T>::ValueOr(T alternative) const {
    if (is_alive_) {
        T copy = *ptr_;
        return copy;
    }
    return alternative;
}

template <class T>
T &Optional<T>::operator*() {
    return *ptr_;
}

template <class T>
T const &Optional<T>::operator*() const {
    return *ptr_;
}

template <class T>
T *Optional<T>::operator->() {
    return ptr_;
}

template <class T>
T const *Optional<T>::operator->() const {
    return ptr_;
}

template <class T>
template <class... Args>
T &Optional<T>::Emplace(Args... args) {
    if (is_alive_) {
        ptr_->~T();
        ptr_ = new (&memory_) T(args...);
    } else {
        is_alive_ = true;
        ptr_ = new (&memory_) T(args...);
    }
    return *ptr_;
}

template <class T>
void Optional<T>::Reset() {
    if (is_alive_) {
        is_alive_ = false;
        ptr_->~T();
    }
}

template <class T>
void Optional<T>::Swap(Optional<T> &other) {
    std::swap(ptr_, other.ptr_);
    std::swap(is_alive_, other.is_alive_);
}

#endif  // OPTIONAL_OPTIONAL_H
