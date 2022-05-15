#pragma once
#include <memory>
#include <vector>


template<typename T, typename alloc = std::allocator<T>>
class Stack
{
public:
    Stack()
        :
        _size(0)
    {
    }

    ~Stack()
    {
        _deinit();
    }

    void push_back(const T &element)
    {
        ptr = _alloc.allocate(1);
        _alloc.construct(ptr, element);
        ++_size;
    }

    T pop()
    {
        if (_size == 0)
            throw std::out_of_range("No elements in stack");
        --_size;
        return std::move(*(ptr));
    }

    int get_size()
    {
        return _size;
    }

    Stack(const Stack &container)
    {
        this->_size = container._size;
        this->_alloc = container._alloc;
        this->ptr = this->_alloc.get_last_element_ptr();
    }

    Stack& operator=(const Stack &container)
    {
        this->_deinit();
        this->_alloc = container._alloc;
        this->_size = container._size;
        this->ptr = this->_alloc.get_last_element_ptr();
        return *this;
    }

    T operator[](const int index)
    {
        if (index >= _size)
            throw std::out_of_range("out of Stack");
        return *(ptr - sizeof(T)*(_size - index - 1));
    }


private:
    int _size{};
    alloc _alloc;
    T* ptr;
    void _deinit() {
        if (ptr != nullptr) {
            for (int i = 0; i <= _size; i++) {
                _alloc.destroy(ptr - sizeof(T)*(_size - i));
                _alloc.deallocate(ptr - sizeof(T)*(_size - i), sizeof(T));
            }
            ptr = nullptr;
            _size = 0;
        }
    }
};