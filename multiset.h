#ifndef MULTISET_H
#define MULTISET_H

#include <ostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include "element_not_found_exception.h"

template <typename T, typename Comp, typename Eq>
class multiset
{
private:
    struct node
    {
        T _value;
        unsigned int _occurrences;
        node *_next;

        node() : _occurrences(0), _next(nullptr) {}
        node(T value) : _occurrences(1), _value(value), _next(nullptr) {}
        node(T value, node *next) : _occurrences(1), _value(value), _next(next) {}
        node(const node &other) : _next(nullptr)
        {
            _value = other._value;
            _occurrences = other._occurrences;
        }

        node &operator=(const node &other)
        {
            if (this != &other)
            {
                node tmp(other);
                std::swap(tmp._value, _value);
                std::swap(tmp._occurrences, _occurrences);
            }
        }

        node &operator==(const node &other)
        {
            return (_value == other._value && _occurrences == other._occurrences);
        }
    };

    node *_head;
    unsigned int _size;
    Comp _cmp;
    Eq _eq;

public:
    multiset() : _head(nullptr), _size(0) {}

    multiset(const multiset &other) : _size(0), _head(nullptr)
    {
        node *curr = other._head;

        try
        {
            while (curr != nullptr)
            {
                add(curr->_value);
                curr = curr->_next;
            }
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

    template <typename Iter>
    multiset(Iter b, Iter e) : _head(nullptr), _size(0)
    {
        try
        {
            for (; b != e; ++b)
            {
                add(static_cast<T>(*b));
            }
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

    multiset &operator=(const multiset &other)
    {
        if (this != &other)
        {
            multiset tmp(other);
            std::swap(_head, tmp._head);
            std::swap(_size, tmp._size);
        }
        return *this;
    }

    template <typename T2, typename Comp2, typename Eq2>
    bool operator==(const multiset<T2, Comp2, Eq2> &other) const
    {
        multiset tmp(other.begin(), other.end());
        const_iterator it = begin();
        const_iterator it2 = tmp.begin();
        if (size() != tmp.size())
        {
            return false;
        }
        while (it != end() && it2 != tmp.end())
        {
            if (*it != *it2)
            {
                return false;
            }
            ++it;
            ++it2;
        }
        return it == end() && it2 == tmp.end();
    }

    template <typename T2, typename Comp2, typename Eq2>
    bool operator!=(const multiset<T2, Comp2, Eq2> &other) const
    {
        return !(*this == other);
    }

    int size() const { return _size; }

    int getOccurrences(const T &value) const
    {
        node *iter = _head;
        while (iter != nullptr)
        {
            if (_eq(iter->_value, value))
            {
                return iter->_occurrences;
            }
            iter = iter->_next;
        }
        return 0;
    }

    void add(const T &value)
    {
        node *tmp;
        try
        {
            tmp = new node(value);
        }
        catch (...)
        {
            throw;
        }

        if (_head == nullptr)
        {
            _head = tmp;
            ++_size;
        }
        else
        {
            node *curr = _head;
            node *prev = _head;
            while (curr != nullptr)
            {
                if (_eq(curr->_value, tmp->_value))
                {
                    curr->_occurrences++;
                    _size++;
                    delete tmp;
                    return;
                }

                if (!_cmp(curr->_value, tmp->_value))
                {
                    prev = curr;
                    curr = curr->_next;
                }
                else
                {
                    if (curr == _head)
                    {
                        _head = tmp;
                        tmp->_next = curr;
                        _size++;
                        return;
                    }
                    else
                    {
                        prev->_next = tmp;
                        tmp->_next = curr;
                        _size++;
                        return;
                    }
                }
            }
            prev->_next = tmp;
            _size++;
        }
    }

    void remove(const T &value)
    {
        node *curr = _head;
        node *prev = _head;
        while (curr != nullptr)
        {
            if (_eq(curr->_value, value))
            {
                if (curr->_occurrences > 1)
                {
                    curr->_occurrences--;
                    _size--;
                    return;
                }
                else
                {
                    if (curr == _head)
                    {
                        _head = curr->_next;
                        delete curr;
                        _size--;
                        return;
                    }
                    else
                    {
                        prev->_next = curr->_next;
                        delete curr;
                        _size--;
                        return;
                    }
                }
            }
            prev = curr;
            curr = curr->_next;
        }
        // se arrivati a questo punto non è stato trovato l'elemento lancio una eccezione
        throw element_not_found_exception("Error, element not found in multiset");
    }

    void clear()
    {
        node *curr = _head;
        while (curr != nullptr)
        {
            node *tmp = curr;
            curr = curr->_next;
            delete tmp;
        }
        _head = nullptr;
        _size = 0;
    }
    bool contains(const T &value) const
    {
        node *curr = _head;
        while (curr != nullptr)
        {
            if (_eq(curr->_value, value))
            {
                return true;
            }
            curr = curr->_next;
        }
        return false;
    }
    bool isEmpty() const { return _size == 0; }

    ~multiset()
    {
        clear();
    }

    friend std::ostream &operator<<(std::ostream &os, const multiset<T, Comp, Eq> &m)
    {
        node *curr = m._head;
        os << "{";
        while (curr != nullptr)
        {
            os << "<" << curr->_value << ", " << curr->_occurrences << ">";
            curr = curr->_next;
            if (curr != nullptr)
            {
                os << ", ";
            }
        }
        os << "}" << std::endl;

        return os;
    }

    class const_iterator
    {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;

        const_iterator() : ptr(nullptr) {}
        const_iterator(const const_iterator &other) : ptr(other.ptr) {}
        const_iterator &operator=(const const_iterator &other)
        {
            if (this != &other)
            {
                ptr = other.ptr;
            }
            return *this;
        }
        const_iterator &operator++()
        {
            if (_counter == ptr->_occurrences)
            {
                ptr = ptr->_next;
                _counter = 1;
            }
            else
            {
                _counter++;
            }

            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            if (_counter == ptr->_occurrences)
            {
                ptr = ptr->_next;
                _counter = 1;
            }
            else
            {
                _counter++;
            }

            return tmp;
        }
        bool operator==(const const_iterator &other) const
        {
            return ptr == other.ptr;
        }
        bool operator!=(const const_iterator &other) const
        {
            return !(ptr == other.ptr);
        }
        reference operator*() const
        {
            return ptr->_value;
        }
        pointer operator->() const
        {
            return &(ptr->_value);
        }

        int occurrences() const
        {
            return ptr->_occurrences;
        }

    private:
        friend class multiset;
        const_iterator(node *p) : ptr(p) {}
        node *ptr;
        unsigned int _counter = 1;
    };

    const_iterator begin() const
    {
        return const_iterator(_head);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }
};

#endif