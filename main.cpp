#include "multiset.h"
#include <iostream>

struct int_descr {
    bool operator()(const int &a, const int &b) 
    {
        return a > b;
    }
};

struct int_cresc
{
    bool operator()(const int &a, const int &b)
    {
        return a < b;
    }
};


struct int_equal {
    bool operator()(const int &a, const int &b) 
    {
        return a == b;
    }
};

int main(int argc, char const *argv[])
{
    multiset<int, int_descr, int_equal> m;
    m.add(1);
    m.add(1);
    m.add(0);
    m.add(2);
    m.add(5);
    m.add(3);
    std::cout << m;
    m.remove(1);
    std::cout << m;
    return 0;
}
