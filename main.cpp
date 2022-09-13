#include "multiset.h"

#include <iostream>
#include <cassert>

/**
    @brief Funtore di ordinamento tra tipi interi

    Ordina due interi in ordine decrescente.
 */
struct decr_int {
    bool operator()(const int &a, const int &b) const {
        return a < b;
    }
};

/**
    @brief Funtore di uguaglianza tra tipi interi

    Determina se due interi sono uguali.
*/
struct equal_int {
    bool operator()(const int &a, const int &b) const {
        return a == b;
    }
};

/**
    @brief Funtore di uguaglianza tra caratteri

    Determina se due caratteri sono uguali.
*/
struct equal_char {
    bool operator()(const char &a, const char &b) const {
        return a == b;
    }
};

/**
    @brief Funtore di ordinamento tra tipi caratteri

    Ordina due caratteri in ordine decrescente.
*/
struct decr_char {
    bool operator()(const char &a, const char &b) const {
        return a < b;
    }
};

/**
    @brief Funtore di ordinamento tra tipi intero

    Ordina due caratteri in ordine ascendente.
*/
struct cresc_int {
    bool operator()(const int &a, const int &b) const {
        return a > b;
    }
};

/**
    @brief Struct che implementa un custom di un intero

    Struct che implementa un custom di un intero.
*/
struct custom_int {
    int value;
    explicit custom_int(int value) : value(value) {}
    custom_int(): value(0) {}
    custom_int(const custom_int &other) : value(other.value) {}
    ~custom_int() {}
    operator int() const {
        return value;
    }
    bool operator==(const custom_int &other) const {
        return value == other.value;
    }
    custom_int &operator=(const custom_int &other) {
        value = other.value;
        return *this;
    }
    bool operator<(const custom_int &other) const {
        return value < other.value;
    }
    bool operator>(const custom_int &other) const {
        return value > other.value;
    }

    friend std::ostream &operator<<(std::ostream &os, const custom_int &w) {
        os << w.value;
        return os;
    }
};

/**
    @brief Funtore di uguaglianza tra custom int

    Determina se due struct di custom_int sono uguali.
*/
struct equal_custom_int {
    bool operator()(const custom_int &a, const custom_int &b) const {
        return a == b;
    }
};

/**
    @brief Funtore di ordinamento tra tipi custom int

    Ordina due custom int in ordine decrescente.
*/
struct decr_custom_int {
    bool operator()(const custom_int &a, const custom_int &b) const {
        return a < b;
    }
};

/**
    @brief Funtore di ordinamento tra tipi custom int

    Ordina due custom int in ordine ascendente.
*/
struct cresc_custom_int {
    bool operator()(const custom_int &a, const custom_int &b) const {
        return a > b;
    }
};

/** 
    @brief test d'uso costruttori con tipi primitivi
*/
void test_constr() {
    multiset<int, decr_int, equal_int> m;
    assert(m.size() == 0);
    
    m.add(1);
    assert(m.size() == 1);

    multiset<int, decr_int, equal_int> m2(m);
    assert(m2.size() == 1);
    m2.add(2);
    assert(m2.size() == 2);

    multiset<int, decr_int, equal_int> m3;
    m3 = m2;
    assert(m3.size() == 2);
    m3.add(3);
    assert(m3.size() == 3);
}

/** 
    @brief test d'uso della funzione isEmpty con tipi primitivi
*/
void test_isEmpty() {
    multiset<int, decr_int, equal_int> m;
    assert(m.isEmpty());
    m.add(1);
    assert(!m.isEmpty());
    m.remove(1);
    assert(m.isEmpty());
}

/** 
    @brief test d'uso della funzione add con tipi primitivi
*/
void test_add() {
    multiset<int, decr_int, equal_int> m;
    m.add(1);
    assert(m.size() == 1);
    assert(m.getOccurrences(1) == 1);
    m.add(1);
    assert(m.size() == 2);
    assert(m.getOccurrences(1) == 2);
    m.add(2);
    assert(m.size() == 3);
    assert(m.getOccurrences(2) == 1);
    m.add(2);
    assert(m.size() == 4);
    assert(m.getOccurrences(2) == 2);
    m.add(3);
    assert(m.size() == 5);
    assert(m.getOccurrences(3) == 1);
    m.add(3);
    assert(m.size() == 6);
    assert(m.getOccurrences(3) == 2);
    m.add(3);
    assert(m.size() == 7);
    assert(m.getOccurrences(3) == 3);
    m.add(2);
    assert(m.size() == 8);
    assert(m.getOccurrences(2) == 3);
}

/** 
    @brief test d'uso della funzione contains con tipi primitivi
*/
void test_contains() {
    multiset<int, decr_int, equal_int> m;
    m.add(1);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(3);
    m.add(5);
    assert(m.contains(1));
    assert(m.contains(2));
    assert(m.contains(3));
    assert(!m.contains(4));
    assert(m.contains(5));
}

/** 
    @brief test d'uso della funzione clear con tipi primitivi
*/
void test_clear() {
    multiset<int, decr_int, equal_int> m;
    m.add(1);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(3);
    m.add(5);
    assert(m.size() == 8);
    m.clear();
    assert(m.size() == 0);
}

/** 
    @brief test d'uso della funzione getOccurences con tipi primitivi
*/
void test_getOccurrences() {
    multiset<int, decr_int, equal_int> m;
    m.add(1);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(3);
    m.add(5);
    assert(m.getOccurrences(1) == 2);
    assert(m.getOccurrences(2) == 2);
    assert(m.getOccurrences(3) == 3);
    assert(m.getOccurrences(4) == 0);
    assert(m.getOccurrences(5) == 1);
}

/** 
    @brief test di stampa con tipi primitivi
*/
void test_operatorOstream() {
    multiset<int, decr_int, equal_int> m;
    m.add(1);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(3);
    m.add(5);
    std::cout << m << std::endl;
}

/** 
    @brief test d'uso dell'operatore == del multiset con tipi primitivi
*/
void test_equals() {
    multiset<int, decr_int, equal_int> m;
    m.add(1);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(3);
    m.add(5);
    multiset<int, decr_int, equal_int> m2;
    m2.add(1);
    m2.add(1);
    m2.add(2);
    m2.add(2);
    m2.add(3);
    m2.add(3);
    m2.add(3);
    m2.add(5);
    assert(m == m2);
    m2.add(5);
    assert(m != m2);
    m2.remove(5);
    assert(m == m2);
    m2.remove(5);
    assert(m != m2);

    multiset<int, cresc_int, equal_int> m3;
    m3.add(1);
    m3.add(1);
    m3.add(2);
    m3.add(2);
    m3.add(3);
    m3.add(3);
    m3.add(3);
    m3.add(5);
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;
    assert(m == m3);
    assert(m2 != m3);
}

/** 
    @brief test d'uso dell'iterator di un multiset con tipi primitivi
*/
void test_const_iterator() {
    multiset<int, decr_int, equal_int> m;
    m.add(8);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(2);
    m.add(9);
    multiset<int, decr_int, equal_int>::const_iterator it = m.begin();

    assert(*it == 9);
    ++it;
    assert(*it == 8);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == m.end());
}

/** 
    @brief test d'uso del costruttore che fa uso degli iterator di multiset con tipi primitivi
*/
void test_constructor_iterator() {
    multiset<int, decr_int, equal_int> m;
    m.add(8);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(2);
    m.add(9);
    multiset<int, decr_int, equal_int> m2(m.begin(), m.end());
    assert(m == m2);

    multiset<int, cresc_int, equal_int> m3(++m.begin(), m.end());
    assert(m3.size() == 7);
    assert(m3.getOccurrences(9) == 0);

    multiset<int, cresc_int, equal_int>::const_iterator it = m3.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 8);
    ++it;
    assert(it == m3.end());


    multiset<char, decr_char, equal_char> m4;
    m4.add('a');
    m4.add('b');
    m4.add('c');
    m4.add('z');
    m4.add('a');
    m4.add('d');

    multiset<int, decr_int, equal_int> m5(m4.begin(), m4.end());
    assert(m5.size() == 6);
    multiset<int, decr_int, equal_int>::const_iterator iter = m5.begin();
    assert(*iter == 122);
    ++iter;
    assert(*iter == 100);
    ++iter;
    assert(*iter == 99);
    ++iter;
    assert(*iter == 98);
    ++iter;
    assert(*iter == 97);
    ++iter;
    assert(*iter == 97);
    ++iter;
    assert(iter == m5.end());
}

/** 
    @brief test d'uso della funzione remove con tipi primitivi
*/
void test_remove() {
    multiset<int, decr_int, equal_int> m;
    m.add(8);
    m.add(1);
    m.add(2);
    m.add(2);
    m.add(3);
    m.add(3);
    m.add(2);
    m.add(9);
    try
    {
        m.remove(10);
    }
    catch(std::runtime_error& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    m.remove(2);
    assert(m.size() == 7);
    assert(m.getOccurrences(2) == 2);
    assert(m.getOccurrences(3) == 2);
    assert(m.getOccurrences(8) == 1);
    assert(m.getOccurrences(9) == 1);
    assert(m.getOccurrences(1) == 1);
    m.remove(2);
    assert(m.size() == 6);
    assert(m.getOccurrences(2) == 1);
    assert(m.getOccurrences(3) == 2);
    assert(m.getOccurrences(8) == 1);
    assert(m.getOccurrences(9) == 1);
    assert(m.getOccurrences(1) == 1);
    m.remove(2);
    assert(m.size() == 5);
    assert(m.getOccurrences(2) == 0);
    assert(m.getOccurrences(3) == 2);
    assert(m.getOccurrences(8) == 1);
    assert(m.getOccurrences(9) == 1);
    assert(m.getOccurrences(1) == 1);
    m.remove(3);
    assert(m.size() == 4);
    assert(m.getOccurrences(2) == 0);
    assert(m.getOccurrences(3) == 1);
    assert(m.getOccurrences(8) == 1);
    assert(m.getOccurrences(9) == 1);
    assert(m.getOccurrences(1) == 1);
    m.remove(3);
    assert(m.size() == 3);
    assert(m.getOccurrences(2) == 0);
    assert(m.getOccurrences(3) == 0);
    assert(m.getOccurrences(8) == 1);
    assert(m.getOccurrences(9) == 1);
    assert(m.getOccurrences(1) == 1);
    m.remove(8);
    assert(m.size() == 2);
    assert(m.getOccurrences(2) == 0);
    assert(m.getOccurrences(3) == 0);
    assert(m.getOccurrences(8) == 0);
    assert(m.getOccurrences(9) == 1);
    assert(m.getOccurrences(1) == 1);
    m.remove(9);
    assert(m.size() == 1);
    assert(m.getOccurrences(2) == 0);
    assert(m.getOccurrences(3) == 0);
    assert(m.getOccurrences(8) == 0);
    assert(m.getOccurrences(9) == 0);
    assert(m.getOccurrences(1) == 1);
    m.remove(1);
    assert(m.size() == 0);
    assert(m.getOccurrences(2) == 0);
    assert(m.getOccurrences(3) == 0);
    assert(m.getOccurrences(8) == 0);
    assert(m.getOccurrences(9) == 0);
    assert(m.getOccurrences(1) == 0);
}

/** 
    @brief test d'uso della funzione delete con tipi primitivi
*/
void test_delete() {
    multiset<int, decr_int, equal_int> *m = new multiset<int, decr_int, equal_int>();
    m->add(8);
    m->add(1);
    m->add(2);
    m->add(2);
    m->add(3);
    m->add(3);
    m->add(2);
    m->add(9);
    assert(m->size() == 8);
    delete m;
    m = nullptr;
}

/** 
    @brief test d'uso dei costruttori con tipi strutturati
*/
void test_constr_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    assert(m.size() == 0);
    
    m.add(custom_int(1));
    assert(m.size() == 1);

    multiset<custom_int, decr_custom_int, equal_custom_int> m2(m);
    assert(m2.size() == 1);
    m2.add(custom_int(2));
    assert(m2.size() == 2);

    multiset<custom_int, decr_custom_int, equal_custom_int> m3;
    m3 = m2;
    assert(m3.size() == 2);
    m3.add(custom_int(3));
    assert(m3.size() == 3);
}

/** 
    @brief test d'uso della funzione add con tipi strutturati
*/
void test_add_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(1));
    assert(m.size() == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.add(custom_int(1));
    assert(m.size() == 2);
    assert(m.getOccurrences(custom_int(1)) == 2);
    m.add(custom_int(2));
    assert(m.size() == 3);
    assert(m.getOccurrences(custom_int(2)) == 1);
    m.add(custom_int(2));
    assert(m.size() == 4);
    assert(m.getOccurrences(custom_int(2)) == 2);
    m.add(custom_int(3));
    assert(m.size() == 5);
    assert(m.getOccurrences(custom_int(3)) == 1);
    m.add(custom_int(3));
    assert(m.size() == 6);
    assert(m.getOccurrences(custom_int(3)) == 2);
    m.add(custom_int(3));
    assert(m.size() == 7);
    assert(m.getOccurrences(custom_int(3)) == 3);
    m.add(custom_int(2));
    assert(m.size() == 8);
    assert(m.getOccurrences(custom_int(2)) == 3);
}

/** 
    @brief test d'uso della funzione contains con tipi strutturati
*/
void test_contains_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(1));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(5));
    assert(m.contains(custom_int(1)));
    assert(m.contains(custom_int(2)));
    assert(m.contains(custom_int(3)));
    assert(m.contains(custom_int(5)));
    assert(!m.contains(custom_int(4)));
}

/** 
    @brief test d'uso della funzione clear con tipi strutturati
*/
void test_clear_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(1));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(5));
    assert(m.size() == 8);
    m.clear();
    assert(m.size() == 0);
}

/** 
    @brief test d'uso della funzione getOccurrences con tipi strutturati
*/
void test_getOccurrences_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(1));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(5));
    assert(m.getOccurrences(custom_int(1)) == 2);
    assert(m.getOccurrences(custom_int(2)) == 2);
    assert(m.getOccurrences(custom_int(3)) == 3);
    assert(m.getOccurrences(custom_int(5)) == 1);
    assert(m.getOccurrences(custom_int(4)) == 0);
}

/** 
    @brief test di stampa di un multiset con tipi strutturati
*/
void test_operatorOstream_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(1));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(5));
    std::cout << m << std::endl;
}

/** 
    @brief test d'uso dell'operator == dei multiset con tipi strutturati
*/
void test_equals_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(1));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(5));
    multiset<custom_int, decr_custom_int, equal_custom_int> m2;
    m2.add(custom_int(1));
    m2.add(custom_int(1));
    m2.add(custom_int(2));
    m2.add(custom_int(2));
    m2.add(custom_int(3));
    m2.add(custom_int(3));
    m2.add(custom_int(3));
    m2.add(custom_int(5));
    assert(m == m2);
    m2.add(custom_int(5));
    assert(m != m2);
    m2.remove(custom_int(5));
    assert(m == m2);
    m2.remove(custom_int(5));
    assert(m != m2);

    multiset<custom_int, cresc_custom_int, equal_custom_int> m3;
    m3.add(custom_int(1));
    m3.add(custom_int(1));
    m3.add(custom_int(2));
    m3.add(custom_int(2));
    m3.add(custom_int(3));
    m3.add(custom_int(3));
    m3.add(custom_int(3));
    m3.add(custom_int(5));
    assert(m == m3);
    assert(m2 != m3);
}

/** 
    @brief test d'uso dell'iterator di un multiset con tipi strutturati 
*/
void test_const_iterator_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(8));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(2));
    m.add(custom_int(9));
    multiset<custom_int, decr_custom_int, equal_custom_int>::const_iterator it = m.begin();
    assert(*it == custom_int(9));
    ++it;
    assert(*it == custom_int(8));
    ++it;
    assert(*it == custom_int(3));
    ++it;
    assert(*it == custom_int(3));
    ++it;
    assert(*it == custom_int(2));
    ++it;
    assert(*it == custom_int(2));
    ++it;
    assert(*it == custom_int(2));
    ++it;
    assert(*it == custom_int(1));
    ++it;
    assert(it == m.end());
}

/** 
    @brief test d'uso del costruttore che fa uso degli iterator di multiset con tipi primitivi
*/
void test_constructor_iterator_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(8));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(2));
    m.add(custom_int(9));
    multiset<custom_int, decr_custom_int, equal_custom_int> m2(m.begin(), m.end());
    assert(m == m2);

    multiset<custom_int, cresc_custom_int, equal_custom_int> m3(++m.begin(), m.end());
    assert(m3.size() == 7);
    assert(m3.getOccurrences(custom_int(9)) == 0);

    multiset<custom_int, cresc_custom_int, equal_custom_int>::const_iterator it = m3.begin();
    assert(*it == custom_int(1));
    ++it;
    assert(*it == custom_int(2));
    ++it;
    assert(*it == custom_int(2));
    ++it;
    assert(*it == custom_int(2));
    ++it;
    assert(*it == custom_int(3));
    ++it;
    assert(*it == custom_int(3));
    ++it;
    assert(*it == custom_int(8));
    ++it;
    assert(it == m3.end());

    multiset<int, decr_int, equal_int> m5(++m3.begin(), m3.end());
    assert(m5.size() == 6);
    multiset<int, decr_int, equal_int>::const_iterator iter = m5.begin();
    assert(*iter == 8);
    ++iter;
    assert(*iter == 3);
    ++iter;
    assert(*iter == 3);
    ++iter;
    assert(*iter == 2);
    ++iter;
    assert(*iter == 2);
    ++iter;
    assert(*iter == 2);
    ++iter;
    assert(iter == m5.end());
}

/** 
    @brief test d'uso della funzione remove con tipi strutturati
*/
void test_remove_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    m.add(custom_int(8));
    m.add(custom_int(1));
    m.add(custom_int(2));
    m.add(custom_int(2));
    m.add(custom_int(3));
    m.add(custom_int(3));
    m.add(custom_int(2));
    m.add(custom_int(9));
    try
    {
        m.remove(custom_int(10));
    }
    catch(std::runtime_error& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    m.remove(custom_int(2));
    assert(m.size() == 7);
    assert(m.getOccurrences(custom_int(2)) == 2);
    assert(m.getOccurrences(custom_int(3)) == 2);
    assert(m.getOccurrences(custom_int(8)) == 1);
    assert(m.getOccurrences(custom_int(9)) == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.remove(custom_int(2));
    assert(m.size() == 6);
    assert(m.getOccurrences(custom_int(2)) == 1);
    assert(m.getOccurrences(custom_int(3)) == 2);
    assert(m.getOccurrences(custom_int(8)) == 1);
    assert(m.getOccurrences(custom_int(9)) == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.remove(custom_int(2));
    assert(m.size() == 5);
    assert(m.getOccurrences(custom_int(2)) == 0);
    assert(m.getOccurrences(custom_int(3)) == 2);
    assert(m.getOccurrences(custom_int(8)) == 1);
    assert(m.getOccurrences(custom_int(9)) == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.remove(custom_int(3));
    assert(m.size() == 4);
    assert(m.getOccurrences(custom_int(2)) == 0);
    assert(m.getOccurrences(custom_int(3)) == 1);
    assert(m.getOccurrences(custom_int(8)) == 1);
    assert(m.getOccurrences(custom_int(9)) == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.remove(custom_int(3));
    assert(m.size() == 3);
    assert(m.getOccurrences(custom_int(2)) == 0);
    assert(m.getOccurrences(custom_int(3)) == 0);
    assert(m.getOccurrences(custom_int(8)) == 1);
    assert(m.getOccurrences(custom_int(9)) == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.remove(custom_int(8));
    assert(m.size() == 2);
    assert(m.getOccurrences(custom_int(2)) == 0);
    assert(m.getOccurrences(custom_int(3)) == 0);
    assert(m.getOccurrences(custom_int(8)) == 0);
    assert(m.getOccurrences(custom_int(9)) == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.remove(custom_int(9));
    assert(m.size() == 1);
    assert(m.getOccurrences(custom_int(2)) == 0);
    assert(m.getOccurrences(custom_int(3)) == 0);
    assert(m.getOccurrences(custom_int(8)) == 0);
    assert(m.getOccurrences(custom_int(9)) == 0);
    assert(m.getOccurrences(custom_int(1)) == 1);
    m.remove(custom_int(1));
    assert(m.size() == 0);
    assert(m.getOccurrences(custom_int(2)) == 0);
    assert(m.getOccurrences(custom_int(3)) == 0);
    assert(m.getOccurrences(custom_int(8)) == 0);
    assert(m.getOccurrences(custom_int(9)) == 0);
    assert(m.getOccurrences(custom_int(1)) == 0);
}

/** 
    @brief test d'uso della funzione delete con tipi strutturati
*/
void test_delete_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> *m = 
        new multiset<custom_int, decr_custom_int, equal_custom_int>();
    m->add(custom_int(8));
    m->add(custom_int(1));
    m->add(custom_int(2));
    m->add(custom_int(2));
    m->add(custom_int(3));
    m->add(custom_int(3));
    m->add(custom_int(2));
    m->add(custom_int(9));
    assert(m->size() == 8);
    delete m;
    m = nullptr;
}

/** 
    @brief test di modifica degli elementi del multiset con tipi strutturati
*/
void test_modify_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    custom_int *w = new custom_int(8);
    custom_int *w2 = new custom_int(1);
    m.add(*w);
    m.add(*w2);
    assert(m.size() == 2);
    assert(m.getOccurrences(*w) == 1);
    assert(m.getOccurrences(*w2) == 1);
    w->value = 2;
    assert(m.size() == 2);
    assert(m.getOccurrences(custom_int(8)) == 1);
    assert(m.getOccurrences(custom_int(2)) == 0);
    assert(m.getOccurrences(custom_int(1)) == 1);
    delete w;
    delete w2;
    assert(m.size() == 2);
    assert(m.getOccurrences(custom_int(8)) == 1);
    assert(m.getOccurrences(custom_int(1)) == 1);
}

/** 
    @brief test d'uso della funzione isEmpty con tipi strutturati
*/
void test_isEmpty_custom() {
    multiset<custom_int, decr_custom_int, equal_custom_int> m;
    assert(m.isEmpty());
    m.add(custom_int(8));
    assert(!m.isEmpty());
    m.remove(custom_int(8));
    assert(m.isEmpty());
}


int main() {
    std::cout << "test_constr..." << std::endl;
    test_constr();
    std::cout << "test_add..." << std::endl;
    test_add();
    std::cout << "test_remove..." << std::endl;
    test_remove();
    std::cout << "test_contains..." << std::endl;
    test_contains();
    std::cout << "test_clear..." << std::endl;
    test_clear();
    std::cout << "test_getOccurrences..." << std::endl;
    test_getOccurrences();
    std::cout << "test_operatorOstream..." << std::endl;
    test_operatorOstream();
    std::cout << "test_equals..." << std::endl;
    test_equals();
    std::cout << "test_const_iterator..." << std::endl;
    test_const_iterator();
    std::cout << "test_constructor_iterator..." << std::endl;
    test_constructor_iterator();
std::cout << "test_isEmpty..." << std::endl;
    test_isEmpty();

    std::cout << "test_constr_custom..." << std::endl;
    test_constr_custom();
    std::cout << "test_add_custom..." << std::endl;
    test_add_custom();
    std::cout << "test_remove_custom..." << std::endl;
    test_remove_custom();
    std::cout << "test_contains_custom..." << std::endl;
    test_contains_custom();
    std::cout << "test_clear_custom..." << std::endl;
    test_clear_custom();
    std::cout << "test_getOccurrences_custom..." << std::endl;
    test_getOccurrences_custom();
    std::cout << "test_operatorOstream_custom..." << std::endl;
    test_operatorOstream_custom();
    std::cout << "test_equals_custom..." << std::endl;
    test_equals_custom();
    std::cout << "test_const_iterator_custom..." << std::endl;
    test_const_iterator_custom();
    std::cout << "test_constructor_iterator_custom..." << std::endl;
    test_constructor_iterator_custom();
    std::cout << "test_isEmpty_custom..." << std::endl;
    test_isEmpty_custom();
    return 0;
}
