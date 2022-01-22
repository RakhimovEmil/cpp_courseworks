#pragma once

#include <utility>

namespace cls09 {
    template<typename T>
    class unique_ptr {
    public:
            unique_ptr() = default;
            unique_ptr(const unique_ptr&) = delete;
            unique_ptr(T* ptr) : ptr(ptr) {}
            unique_ptr(unique_ptr&& x) noexcept : ptr(x.ptr) { x.ptr = nullptr; }

            unique_ptr& operator=(const unique_ptr&) = delete;
            unique_ptr& operator=(unique_ptr&& x) noexcept {
                if (&x == this) {
                    return *this;
                }
                delete ptr;
                ptr = x.ptr;
                x.ptr = nullptr;
                return *this;
            }

            explicit operator bool() const { return ptr != nullptr; }

            T* operator->() { return ptr;  }
            T  operator*()  { return *ptr; }

            T* get()     { return ptr; }
            T* release() {
                T* copy = ptr;
                ptr = nullptr;
                return copy;
            }

            void reset(T* x = nullptr) {
                delete ptr;
                ptr = x;
            }

            ~unique_ptr() { delete ptr; }

    private:
        T* ptr = nullptr;
    };

    template<typename T, typename... U>
    unique_ptr<T> make_unique(U&&... args) {
        return unique_ptr<T>(new T(std::forward<U>(args)...));
    }
}