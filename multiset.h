#ifndef MULTISET_H
#define MULTISET_H

#include <ostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include "element_not_found_exception.h"
/**
 * @brief Classe templata che implementa un MultiSet
 *
 * @tparam T tipo del dato
 * @tparam Comp funtore di comparazione
 * @tparam Eq funtore di equivalenza
 */
template <typename T, typename Comp, typename Eq>
class multiset
{
private:
    /**
     * @brief Nodo della linked list
     *  Contiene il dato e il puntatore al nodo successivo e il numero di occorrenze del dato
     */
    struct node
    {
        T _value;
        unsigned int _occurrences;
        node *_next;
        // Costruttore di default
        node() : _occurrences(0), _next(nullptr) {}
        /**
         * @brief Costruttore di un nuovo oggetto node
         * Inizializza un nuovo nodo con il valore passato come parametro senza un nodo successivo
         * @param value Valore da assegnare al nodo
         */
        node(T value) : _occurrences(1), _value(value), _next(nullptr) {}
        /** 
         * @brief Costruttore di un nuovo oggetto node
         * Inizializza un nuovo nodo con il valore passato come parametro e il nodo successivo
         * @param value Valore da assegnare al nodo
         * @param next Nodo successivo
         */
        node(T value, node *next) : _occurrences(1), _value(value), _next(next) {}
        /** 
         * @brief Copy constructor
         * Inizializza un nuovo nodo con un nodo passato come parametro
         * @param other Nodo da copiare
         */
        node(const node &other) : _next(nullptr)
        {
            _value = other._value;
            _occurrences = other._occurrences;
        }
        /**
         * @brief Operatore di assignement
         * Assegna un nodo ad un altro nodo
         * @param other Nodo da copiare
         * @return node& Nodo copiato
         */
        node &operator=(const node &other)
        {
            if (this != &other)
            {
                node tmp(other);
                std::swap(tmp._value, _value);
                std::swap(tmp._occurrences, _occurrences);
            }
        }
        /** 
         * @brief Operatore di uguaglianza
         * Controlla se due nodi sono uguali confrontando il valore e il numero di occorrenze
         */
        node &operator==(const node &other)
        {
            return (_value == other._value && _occurrences == other._occurrences);
        }
        
        /**
         * @brief Operatore di disuguaglianza
         * Controlla se due nodi sono diversi confrontando il valore e il numero di occorrenze
         */
        node &operator!=(const node &other) {
            return !(*this == other);
        }

        /**
         * @brief Distruttore
         * Distrugge il nodo
         */
        ~node() {
            _next = nullptr;
        }
    };

    node *_head;
    unsigned int _size;
    Comp _cmp;
    Eq _eq;

public:
    /**
     * @brief Costruttore di default
     * Inizializza un nuovo multiset vuoto
     */
    multiset() : _head(nullptr), _size(0) {}

    /**
     * @brief Costruttore di copia
     * Inizializza un nuovo multiset con un multiset passato come parametro
     * @param other Multiset da copiare
     */
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

    /**
     * @brief Costruttore di copia tramite iteratore
     * Inizializza un nuovo multiset con due iteratori passati come parametro
     * @param begin Iteratore all'inizio del range
     * @param end Iteratore alla fine del range
     */
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

    /**
     * @brief Operatore di assignement
     * Assegna un multiset ad un altro multiset
     * @param other Multiset da copiare
     * @return multiset& Multiset copiato
     */
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

    /**
     * @brief Operatore di uguaglianza
     * Controlla se due multiset sono uguali confrontando tutti i valori dei nodi e il numero di occorrenze di ogni nodo
     * E' templata per permettere la comparazione tra multiset di tipi diversi
     * @param other Multiset da confrontare
     * @return true 
     * @return false 
     */
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

    /**
     * @brief Operatore di disuguaglianza
     * Controlla se due multiset sono diversi confrontando tutti i valori dei nodi e il numero di occorrenze di ogni nodo
     * E' templata per permettere la comparazione tra multiset di tipi diversi
     * @param other Multiset da confrontare
     * @return true 
     * @return false 
     */
    template <typename T2, typename Comp2, typename Eq2>
    bool operator!=(const multiset<T2, Comp2, Eq2> &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Size
     * Ritorna il numero di nodi presenti nel multiset
     * 
     * @return int 
     */
    int size() const { return _size; }

    /**
     * @brief Get the Occurrences
     * Ritorna il numero di occorrenze di un valore nel multiset
     * @param value 
     * @return int 
     */
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

    /**
     * @brief Add
     * Aggiunge un valore al multiset
     * @param value 
     */
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

    /**
     * @brief Remove
     * Rimuove un valore dal multiset
     * @param value 
     */
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

    /**
     * @brief Clear
     * Svuota il multiset
     */
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

    /** 
     * @brief Contains
     * Controlla se un valore è presente nel multiset
     * @param value Valore da cercare
    */
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

    /**
     * @brief Is Empty
     * Controlla se il multiset è vuoto 
     * @return true 
     * @return false 
     */
    bool isEmpty() const { return _size == 0; }

    /**
     * @brief Distruttore
     * Distrugge il multiset
     */
    ~multiset()
    {
        clear();
    }

    /**
     * @brief Operatore <<
     * Stampa su uno stream il multiset nel formato <valore1, occorrenze1>, <valore2, occorrenze2>, ...
     * @param os 
     * @param m 
     * @return std::ostream& 
     */
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

    /**
     * @brief Const Iterator
     * Iteratore costante per il multiset
     */
    class const_iterator
    {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;

        // Costruttore di default
        const_iterator() : ptr(nullptr) {}
        // Copy constructor
        const_iterator(const const_iterator &other) : ptr(other.ptr) {}
        // Operatore di assegnamento
        const_iterator &operator=(const const_iterator &other)
        {
            if (this != &other)
            {
                ptr = other.ptr;
            }
            return *this;
        }
        // Operatore di pre-incremento
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
        // Operatore di post-incremento
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
        // Operatore di ugualianza
        bool operator==(const const_iterator &other) const
        {
            return ptr == other.ptr;
        }
        // Operatore di disuguaglianza
        bool operator!=(const const_iterator &other) const
        {
            return !(ptr == other.ptr);
        }
        // Operatore di dereferenziazione
        reference operator*() const
        {
            return ptr->_value;
        }
        // Operatore che ritorna il puntatore
        pointer operator->() const
        {
            return &(ptr->_value);
        }
        // Ritorna il numero di occorrenze dell'elemento puntato
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
    /**
     * @brief Ritorna un iteratore costante all'inizio del multiset
     * 
     * @return const_iterator 
     */
    const_iterator begin() const
    {
        return const_iterator(_head);
    }
    /**
     * @brief Ritorna un iteratore costante alla fine del multiset
     * 
     * @return const_iterator 
     */
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }
};

#endif