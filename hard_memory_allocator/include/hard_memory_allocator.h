#pragma once

#include "cstring"
#include "iostream"

template <typename T, const std::size_t size_of_container, bool auto_increase_size = false, bool deallocate_all_memory_in_one_time = false>
struct hard_memory_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    void* ptr;
    int current_element{};
    int current_memory_pack{};
    int size_of_container_local;

    template<typename U>
    struct rebind {
        using other = hard_memory_allocator<U, size_of_container, auto_increase_size, deallocate_all_memory_in_one_time>;
    };

    hard_memory_allocator()
    {
        current_element = 0;
        current_memory_pack = 1;
        ptr = std::malloc(size_of_container * sizeof(T));
        size_of_container_local = size_of_container;
    }
    ~hard_memory_allocator() = default;

    template<typename U>
    hard_memory_allocator(const hard_memory_allocator<U, size_of_container, auto_increase_size, deallocate_all_memory_in_one_time>&){}

    T *allocate(std::size_t n) {

        if (!ptr)
            throw std::bad_alloc();

        if (auto_increase_size && (current_element > size_of_container - 1)) {
            current_element = 0;
            ++current_memory_pack;
            auto new_ptr = ptr;
            ptr = std::malloc(size_of_container * sizeof(T)*current_memory_pack);
            if (!(new_ptr && ptr))
                throw std::bad_alloc();
            memcpy(ptr, new_ptr, size_of_container * sizeof(T)*(current_memory_pack -1));
        }
        else if (current_element > size_of_container - 1) {
            std::free(ptr);
            throw std::out_of_range("you should to increase size of container");
        }
        const auto _ptr = reinterpret_cast<T *>(ptr) + sizeof(T) * current_element;
        ++current_element;
        return _ptr;
    }

    void deallocate(T *p, std::size_t n) {
        if (!deallocate_all_memory_in_one_time) {
            if (p != nullptr) {
//                std::free(p);
                p = nullptr;
            }
        }
        else if (ptr != nullptr) {
            std::free(ptr);
            ptr = nullptr;
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }


    hard_memory_allocator& operator=(const hard_memory_allocator &alloc) {
        if (this->ptr)
            std::free(this->ptr);
        this->size_of_container_local = alloc.size_of_container_local;
        this->current_memory_pack = alloc.current_memory_pack;
        this->ptr = std::malloc(size_of_container * sizeof(T)*current_memory_pack);
        this->current_element = alloc.current_element;
        if (!ptr)
            throw std::bad_alloc();
        memcpy(ptr, alloc.ptr, size_of_container_local * sizeof(T)*current_memory_pack);
        return *this;
    }

    T* get_last_element_ptr() {return reinterpret_cast<T *>(ptr)+ sizeof(T) * ((current_element - 1) + (current_memory_pack - 1) * size_of_container_local);}
};