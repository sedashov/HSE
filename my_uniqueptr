// my unique_ptr class on C++ (simplified) 
#include <cstddef>
#include <iostream>
#include <memory>
#include <tuple>

template <typename T,
        class Deleter = std::default_delete<T>>
class UniquePtr {
private:
    std::tuple<T*, Deleter> ptr;

public:
    explicit UniquePtr() noexcept {
        std::get<T*>(ptr) = nullptr;
    }

    explicit UniquePtr(T* other) noexcept {
        std::get<T*>(ptr) = other;
    }

    explicit UniquePtr(T* other, Deleter del) noexcept {
        std::get<T*>(ptr) = other;
        std::get<Deleter>(ptr) = del;
    }

    explicit UniquePtr(UniquePtr<T, Deleter>&& other) noexcept {
        std::get<T*>(ptr) = std::get<T*>(other.ptr);
        std::get<Deleter>(ptr) = std::get<Deleter>(other.ptr);
        std::get<T*>(other.ptr) = nullptr;
    }

    explicit UniquePtr(std::nullptr_t other) {
        std::get<T*>(ptr) = other;
    }

    UniquePtr& operator =(std::nullptr_t other) {
        std::get<Deleter>(ptr)(std::get<T*>(ptr));
        std::get<T*>(ptr) = other;
        other = nullptr;
        return *this;
    }

    UniquePtr& operator =(UniquePtr<T, Deleter>&& other) {
        std::get<Deleter>(ptr)(std::get<T*>(ptr));
        std::get<T*>(ptr) = std::get<T*>(other.ptr);
        std::get<Deleter>(ptr) = std::get<Deleter>(other.ptr);
        std::get<T*>(other.ptr) = nullptr;
        return *this;
    }

    ~UniquePtr() noexcept {
        std::get<Deleter>(ptr)(std::get<T*>(ptr));
    }

    UniquePtr operator =(UniquePtr<T, Deleter>& other) = delete;
    UniquePtr(UniquePtr<T, Deleter>& other) = delete;

    explicit operator bool() const noexcept {
        return std::get<T*>(ptr) != nullptr;
    }

    T* release() noexcept {
        auto tmp = std::get<T*>(ptr);
        std::get<T*>(ptr) = nullptr;
        return tmp;
    }

    void reset(T* other) noexcept {
        std::get<Deleter>(ptr)(std::get<T*>(ptr));
        std::get<T*>(ptr) = other;
        other = nullptr;
    }

    T& operator *() const {
        return *std::get<T*>(ptr);
    }

    T& operator *() {
        return *std::get<T*>(ptr);
    }

    T* operator ->() const noexcept {
        return std::get<T*>(ptr);
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(std::get<T*>(ptr), std::get<T*>(other.ptr));
        std::swap(std::get<Deleter>(ptr), std::get<Deleter>(other.ptr));
    }

    T* get() const noexcept {
        return std::get<T*>(ptr);
    }

    const Deleter& get_deleter() const {
        return std::get<Deleter>(ptr);
    }

    Deleter& get_deleter() {
        return std::get<Deleter>(ptr);
    }
};

