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
        _list_of_ptr.reserve(5);
    }

    ~Stack()
    {
        if (!_list_of_ptr.empty()) {
            for (auto &current_element: _list_of_ptr) {
                _alloc.destroy(current_element);
                _alloc.deallocate(current_element, sizeof(T));
            }
            _list_of_ptr.clear();
            _size = 0;
        }
    }

    void push_back(const T &element)
    {
        auto _ptr = _alloc.allocate(1);
        _list_of_ptr.push_back(_ptr);
        _alloc.construct(_ptr, element);
        ++_size;
    }

    T pop()
    {
        if (_size == 0)
            throw std::out_of_range("No elements in stack");
        --_size;
        auto top_element = std::move(*_list_of_ptr[_size]);
        _alloc.destroy(_list_of_ptr[_size]);
        _alloc.deallocate(_list_of_ptr[_size], sizeof(T));
        _list_of_ptr.pop_back();
        return top_element;
    }

    int get_size()
    {
        return _size;
    }

    Stack(const Stack<T> &container)
    {
        for (const auto &current_ptr : container._list_of_ptr) {
            this->push_back(*current_ptr);
        }
    }

    Stack operator=(const Stack<T> &container)
    {
        this->_list_of_ptr.clear();
        for (const auto &current_ptr : container._list_of_ptr) {
            this->push_back(*current_ptr);
        }
        return container;
    }

    T operator[](const int index)
    {
        if (index >= _size)
            throw std::out_of_range("out of Stack");
        return *_list_of_ptr[index];
    }


private:
    int _size;
    std::vector<T *> _list_of_ptr;
    alloc _alloc;
};