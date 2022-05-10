#pragma once

#include "vector"
#include "iostream"

template <typename T, const std::size_t size_of_container, bool auto_increase_size = false>
struct hard_memory_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    std::vector<void*> list_of_memory;
    int current_element;
    int current_memory_pack;

    template<typename U>
    struct rebind {
        using other = hard_memory_allocator<U, size_of_container, auto_increase_size>;
    };

    hard_memory_allocator() :
        current_element{0},
        current_memory_pack{0}
    {
        list_of_memory.reserve(5);
        auto ptr = std::malloc(size_of_container * sizeof(T));
        list_of_memory.push_back(ptr);
    }
    ~hard_memory_allocator() = default;

    template<typename U>
    explicit hard_memory_allocator(const hard_memory_allocator<U, size_of_container, auto_increase_size>&){}

    T *allocate(std::size_t n) {
        if (!list_of_memory[current_memory_pack])
            throw std::bad_alloc();
        if (auto_increase_size && (current_element > size_of_container - 1)) {
            current_element = 0;
            ++current_memory_pack;
            auto ptr = std::malloc(size_of_container * sizeof(T));
            list_of_memory.push_back(ptr);
        }
        else if (current_element > size_of_container - 1) {
            deallocate(nullptr, 0);
            throw std::out_of_range("you should to increase size of container");
        }
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        auto _ptr = reinterpret_cast<T *>(list_of_memory[current_memory_pack]) + sizeof(T) * current_element;
        std::cout << _ptr << std::endl;
        ++current_element;
        return _ptr;
    }

    void deallocate(T *p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        if (!list_of_memory.empty()) {
            for (auto &current_pack: list_of_memory) {
                std::cout << current_pack << std::endl;
                if (current_pack) {
                    std::free(current_pack);
                    current_pack = nullptr;
                }
            }
            list_of_memory.clear();
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~T();
    }
};