#pragma once

#include <iostream>

using namespace std;

template <class T, unsigned S>
struct std_11_simple_allocator {
    using value_type = T;
    unsigned max_size = S;
    void* memory = nullptr;
    unsigned cnt = 0;

    std_11_simple_allocator () noexcept {}
    template <class U, unsigned M> std_11_simple_allocator(const std_11_simple_allocator<U,M>& ) noexcept {}

    ~std_11_simple_allocator()
    {
        if(memory != nullptr){
            cnt = 0;
            free(memory);
            memory = nullptr;
        }
        cout << "all DTOR" << endl;
    }

    template <class U>
    struct rebind {
        using other = std_11_simple_allocator<U, S>;
    };

    T* allocate (std::size_t n)
    {
        if(memory == nullptr){
            memory = malloc(max_size*sizeof(T));
            if(memory == nullptr) throw bad_alloc();
            cout << "all init: " << (void*)memory <<endl;
        } else if(n > max_size) {
            cout << "all ERROR" << endl;
            throw bad_alloc();
        }
        if (cnt + n <= max_size) {
            auto chunk = reinterpret_cast<T *>(memory) + cnt;
            cnt += n;
            cout << "all: " << (void*)chunk << endl;
            return chunk;
        } else {
            cout << "all ERROR CNT" << endl;
            throw bad_alloc();
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void deallocate ([[maybe_unused]] T* p, [[maybe_unused]]std::size_t n)
    {
        // ::operator delete(p);
    }

    void destroy(T *p)
    {
        p->~T();
    }

};

template <class T, unsigned U,  class TA, unsigned UA>
constexpr bool operator== (const std_11_simple_allocator<T,U>& a1, const std_11_simple_allocator<TA,UA>& a2) noexcept
{
    return true;
}

template <class T, unsigned U, class TA, unsigned UA>
constexpr bool operator!= (const std_11_simple_allocator<T,U>& a1, const std_11_simple_allocator<TA,UA>& a2) noexcept
{
    return false;
}
