//
// Created by thunderfox on 17/10/20.
//

#include "sgc_ptr.h"

template<class T, int size>
bool sgc_ptr<T, size>::first_created = true;

template<class T, int size>
typename std::list<sgc_info<T>>::iterator sgc_ptr<T, size>::find_sgc_info(T *T_ptr) {
    sgc_info<T> temp = T_ptr;
    for (auto it = gc_list.begin(); it != gc_list.end(); it++) {
        if (*it == temp)
            return it;
    }
    return gc_list.end();
}

template<class T, int size>
sgc_ptr<T, size>::sgc_ptr(T *T_ptr) {
    if (first_created) atexit(clear_gc_list);
    first_created = false;
    typename std::list<sgc_info<T>>::iterator gc_list_itr = find_sgc_info(T_ptr);
    if (gc_list_itr == gc_list.end()) {
        gc_list.push_front(sgc_info<T>(T_ptr, size));
    } else {
        gc_list_itr->set_ref_count(gc_list_itr->get_ref_count() + 1);
    }
    mem_location = T_ptr;
    array_size = size;
    if (size > 0)
        is_array = true;
    else
        is_array = false;
#ifdef DEBUG_SGC_PTR
    std::cout << "Constructing sgc_ptr";
    if (is_array)
        std::cout << ", size is :" << array_size;
    std::cout << std::endl;
#endif
}


template<class T, int size>
sgc_ptr<T, size>::sgc_ptr(const sgc_ptr &other) {
    auto gc_list_itr = find_sgc_info(other.mem_location);

    gc_list_itr->set_ref_count(gc_list_itr->get_ref_count() + 1);

    mem_location = other.mem_location;
    is_array = other.is_array;
    array_size = other.array_size;

#ifdef DEBUG_SGC_PTR
    std::cout << "Constructing sgc_ptr";
    if (is_array)
        std::cout << ", size is :" << array_size;
    std::cout << std::endl;
#endif
}

template<class T, int size>
sgc_ptr<T, size>::~sgc_ptr() {

}

template<class T, int size>
bool sgc_ptr<T, size>::collect() {

}

template<class T, int size>
T *sgc_ptr<T, size>::operator=(T *T_ptr) {
    return nullptr;
}

template<class T, int size>
sgc_ptr<T, size> &sgc_ptr<T, size>::operator=(sgc_ptr &other) {

}

template<class T, int size>
T &sgc_ptr<T, size>::operator*() const {

}

template<class T, int size>
T *sgc_ptr<T, size>::operator->() {
    return nullptr;
}

template<class T, int size>
T &sgc_ptr<T, size>::operator[](unsigned int i) const {

}

template<class T, int size>
sgc_ptr<T, size>::operator T *() {
    return nullptr;
}

template<class T, int size>
typename sgc_ptr<T, size>::iterator sgc_ptr<T, size>::begin() {
    return sgc_ptr::iterator();
}

template<class T, int size>
typename sgc_ptr<T, size>::iterator sgc_ptr<T, size>::end() {
    return sgc_ptr::iterator();
}

template<class T, int size>
unsigned sgc_ptr<T, size>::get_gc_list_size() {
    return 0;
}

template<class T, int size>
void sgc_ptr<T, size>::show_list() {

}

template<class T, int size>
void sgc_ptr<T, size>::clear_gc_list() {

}