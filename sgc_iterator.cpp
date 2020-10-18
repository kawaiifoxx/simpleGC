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

/*Returns size of the array*/
template<class T>
unsigned int sgc_iterator<T>::size() const {
    return length;
}

/*
 * dereferences current object pointed by iterator and returns it's reference
 * Throws std::out_of_range exception if iterator is on or past end or before start.
 */
template<class T>
T &sgc_iterator<T>::operator*() const {
    if (ptr < begin || ptr >= end)
        throw std::out_of_range("Out of range access in sgc_iterator.");
    return *ptr;
}

/*
 * returns address of current object pointed by iterator
 * Throws std::out_of_range exception if iterator is out of range.
 */
template<class T>
T *sgc_iterator<T>::operator->() const {
    if (ptr < begin || ptr >= end)
        throw std::out_of_range("Out of range access in sgc_iterator.");
    return ptr;
}

/*Prefix ++*/
template<class T>
sgc_iterator<T> sgc_iterator<T>::operator++() {
    ptr++;
    return *this;
}

/*Prefix --*/
template<class T>
sgc_iterator<T> sgc_iterator<T>::operator--() {
    ptr--;
    return *this;
}

/*Postfix ++*/
template<class T>
sgc_iterator<T> sgc_iterator<T>::operator++(int not_used) {
    auto temp = *this;
    ptr++;
    return temp;
}

/*Postfix --*/
template<class T>
sgc_iterator<T> sgc_iterator<T>::operator--(int not_used) {
    auto temp = *this;
    ptr++;
    return temp;
}

/*
 * returns a reference of object at specified index.
 * Throws  std::out_of_range exception if you try to access, out of bound memory locations.
 */
template<class T>
T &sgc_iterator<T>::operator[](unsigned int i) const {
    if (ptr + i < begin && ptr + i >= end)
        throw std::out_of_range("Out of range access in sgc_iterator");
    return *(ptr + i);
}

/*Boolean Comparison Operator*/
template<class T>
bool sgc_iterator<T>::operator==(const sgc_iterator &itr2) const {
    return this->ptr == itr2.ptr;
}

/*Boolean Comparison Operator*/
template<class T>
bool sgc_iterator<T>::operator>=(const sgc_iterator &itr2) const {
    return this->ptr >= itr2.ptr;
}

/*Boolean Comparison Operator*/
template<class T>
bool sgc_iterator<T>::operator<=(const sgc_iterator &itr2) const {
    return this->ptr <= itr2.ptr;
}

/*Boolean Comparison Operator*/
template<class T>
bool sgc_iterator<T>::operator!=(const sgc_iterator &itr2) const {
    return this->ptr != itr2.ptr;
}

/*Boolean Comparison Operator*/
template<class T>
bool sgc_iterator<T>::operator<(const sgc_iterator &itr2) const {
    return this->ptr < itr2.ptr;
}

/*Boolean Comparison Operator*/
template<class T>
bool sgc_iterator<T>::operator>(const sgc_iterator &itr2) const {
    return this->ptr > itr2.ptr;
}
/*
 * Returns iterator pointing to memory location  [<memory location pointed by this iterator> + n].
 * No bound checking is performed in this operation be careful!
 */
template<class T>
sgc_iterator<T> sgc_iterator<T>::operator+(int n) const {
    ptr += n;
    return *this;
}
/*Returns difference of two iterators.*/
template<class T>
int sgc_iterator<T>::operator-(sgc_iterator<T> itr2) const {
    return ptr - itr2.ptr;
}
