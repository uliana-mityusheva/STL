#ifndef ANY_ANY_H
#define ANY_ANY_H

#include <iostream>
#include <memory>

class BadAnyCast : public std::bad_cast {};

class IBase {
public:
    virtual std::unique_ptr<IBase> Clone() = 0;
    virtual ~IBase() = default;
};

template <class T>
class Derived : public IBase {
private:
    T value_;

public:
    ~Derived() override = default;
    Derived() = default;
    explicit Derived(const T &value);

    T &Get();

    std::unique_ptr<IBase> Clone() override;
    std::unique_ptr<Derived<T>> CloneType();
};

class Any {
private:
    std::unique_ptr<IBase> ptr_;

public:
    Any();
    Any(const Any &other);
    Any(Any &&other) noexcept;

    Any &operator=(const Any &other);
    Any &operator=(Any &&other) noexcept;

    template <class T>
    Any(const T &value);  // NOLINT

    template <class T>
    Any &operator=(const T &value);

    void Swap(Any &other);
    void Reset();
    bool HasValue();

    template <class T>
    friend T AnyCast(const Any &value);
};

template <class T>
Derived<T>::Derived(const T &value) {
    value_ = value;
}

template <class T>
std::unique_ptr<IBase> Derived<T>::Clone() {
    return CloneType();
}

template <class T>
T &Derived<T>::Get() {
    return value_;
}

inline void Any::Reset() {
    ptr_ = nullptr;
}

template <class T>
std::unique_ptr<Derived<T>> Derived<T>::CloneType() {
    return std::make_unique<Derived<T>>(value_);
}

inline Any::Any() : ptr_(nullptr) {
}

template <class T>
Any::Any(const T &value) : ptr_(new Derived<T>(value)) {
}

inline Any::Any(Any &&other) noexcept {
    *this = std::move(other);
    other.Reset();
}

inline Any &Any::operator=(const Any &other) {
    ptr_ = other.ptr_->Clone();
    return *this;
}

inline Any &Any::operator=(Any &&other) noexcept {
    ptr_ = other.ptr_->Clone();
    other.Reset();
    return *this;
}

template <class T>
Any &Any::operator=(const T &value) {
    ptr_.reset(new Derived<T>(value));
    return *this;
}

inline Any::Any(const Any &other) : ptr_(other.ptr_->Clone()) {
}

inline bool Any::HasValue() {
    return !(ptr_ == nullptr);
}

inline void Any::Swap(Any &other) {
    ptr_.swap(other.ptr_);
}

template <class T>
T AnyCast(const Any &value) {
    if (dynamic_cast<Derived<T> *>(value.ptr_.get())) {
        auto ptr = dynamic_cast<Derived<T> *>(value.ptr_.get());
        return ptr->Get();
    }
    throw BadAnyCast{};
}

#endif  // ANY_ANY_H
