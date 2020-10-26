//
// Created by thunderfox on 17/10/20.
//

#include "sgc_info.h"

template<class T>
sgc_info<T>::sgc_info(T *mem_ptr, int size) {
    ref_count = 1;
    this->mem_ptr = mem_ptr;
    if (!size)
        is_array = false;
    else
        is_array = true;
    length = size;
}

template<class T>
unsigned int sgc_info<T>::get_ref_count() const {
    return ref_count;
}

template<class T>
void sgc_info<T>::set_ref_count(unsigned int ref_count) {
    this->ref_count = ref_count;
}

template<class T>
bool sgc_info<T>::operator==(sgc_info other) const {
    return this->mem_ptr == other.mem_ptr;
}

template<class T>
bool sgc_info<T>::get_is_array() const {
    return is_array;
}

template<class T>
T *sgc_info<T>::get_mem_location() const {
    return mem_ptr;
}

template<class T>
unsigned int sgc_info<T>::size() const {
    return length;
}
