//
// Created by thunderfox on 17/10/20.
//

#ifndef SIMPLEGC_SGC_ITERATOR_H
#define SIMPLEGC_SGC_ITERATOR_H

#include <stdexcept>

/*
 * Iterator class for iterating over a array of objects.
 *
 * Iterator class does not take part in garbage collection.
 */
template<class T>
class sgc_iterator {
    /* points at the start of the array */
    T *begin;
    /* points at the one past last object of the array */
    T *end;
    /* points at current object of array */
    T *ptr;
    unsigned length{};

public:
    sgc_iterator();

    sgc_iterator(T *begin, unsigned int size);

    sgc_iterator(T *begin, T *end, T *ptr);

    unsigned int size() const;

    T &operator*() const;

    T *operator->() const;

    sgc_iterator<T> operator++();

    sgc_iterator<T> operator--();

    sgc_iterator<T> operator++(int not_used);

    sgc_iterator<T> operator--(int not_used);

    T &operator[](unsigned i) const;

    bool operator==(const sgc_iterator &itr2) const;

    bool operator>=(const sgc_iterator &itr2) const;

    bool operator<=(const sgc_iterator &itr2) const;

    bool operator!=(const sgc_iterator &itr2) const;

    bool operator<(const sgc_iterator &itr2) const;

    bool operator>(const sgc_iterator &itr2) const;

    sgc_iterator<T> operator+(int n) const;

    int operator-(sgc_iterator<T> itr2) const;
};


#endif //SIMPLEGC_SGC_ITERATOR_H
