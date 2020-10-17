//
// Created by thunderfox on 17/10/20.
//

#include "sgc_iterator.h"

template<class T>
sgc_iterator<T>::sgc_iterator() {
    ptr = begin = end = nullptr;
}

template<class T>
sgc_iterator<T>::sgc_iterator(T *begin, unsigned int size) {
    ptr = this->length = size;
    this->begin = begin;
    end = begin + size;
}

template<class T>
sgc_iterator<T>::sgc_iterator(T *begin, T *end, T *ptr):begin(begin), end(end), ptr(ptr) {
    length = end - begin;
}

template<class T>
unsigned int sgc_iterator<T>::size() const {
    return length;
}

