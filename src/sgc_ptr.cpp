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
#ifdef DEBUG_SGC_PTR
    std::cout << "SGC_PTR going out of scope" << std::endl;
#endif
    auto p = find_sgc_info(mem_location);
    p->set_ref_count(p->get_ref_count() - 1);
    collect();
}

template<class T, int size>
bool sgc_ptr<T, size>::collect() {
    bool mem_freed = false;
#ifdef DEBUG_SGC_PTR
    std::cout << "Before Garbage collection :";
    show_list();
#endif
    typename std::list<sgc_info<T>>::iterator p;
    do {
        /*Scanning for zero reference pointers*/
        for (p = gc_list.begin(); p != gc_list.end(); p++) {
            if (p->get_ref_count() > 0) continue;
            mem_freed = true;

            /*Check if nullptr*/
            if (p->get_mem_location()) {
                /*Check if ptr is array.*/
                if (p->get_is_array()) {
#ifdef DEBUG_SGC_PTR
                    std::cout << "Deleting Array of Size: ";
                    std::cout << p->size() << std::endl;
#endif
                    delete[] p->get_mem_location();
                } else {
#ifdef DEBUG_SGC_PTR
                    std::cout << "Deleting Pointer " << p->get_mem_location() << std::endl;
#endif
                    delete p->get_mem_location();
                }
            }
            break;
        }
    } while (p != gc_list.end());
#ifdef DEBUG_SGC_PTR
    std::cout << "After Garbage Collection :";
    show_list();
#endif
    return mem_freed;
}

template<class T, int size>
T *sgc_ptr<T, size>::operator=(T *T_ptr) {
    auto p = find_sgc_info(mem_location);
    p->set_ref_count(p->get_ref_count() - 1);
    p = find_sgc_info(T_ptr);
    /*Check if T_ptr exist in gc_list*/
    if (p != gc_list.end()) {
        p->set_ref_count(p->get_ref_count() + 1);
    } else {
        gc_list.push_front({T_ptr, size});
    }
    mem_location = T_ptr;
    return T_ptr;
}

template<class T, int size>
sgc_ptr<T, size> &sgc_ptr<T, size>::operator=(sgc_ptr &other) {
    auto p = find_sgc_info(mem_location);
    p->set_ref_count(p->get_ref_count() - 1);
    p = find_sgc_info(other.mem_location);
    p->set_ref_count(p->get_ref_count() + 1);
    mem_location = other.mem_location;
    return *this;
}

template<class T, int size>
T &sgc_ptr<T, size>::operator*() const {
    return *mem_location;
}

template<class T, int size>
T *sgc_ptr<T, size>::operator->() {
    return mem_location;
}

template<class T, int size>
T &sgc_ptr<T, size>::operator[](unsigned int i) const {
    return mem_location[i];
}

template<class T, int size>
sgc_ptr<T, size>::operator T *() {
    return mem_location;
}

template<class T, int size>
typename sgc_ptr<T, size>::iterator sgc_ptr<T, size>::begin() {
    int arr_size;
    if (is_array) arr_size = array_size;
    else arr_size = 1;
    return sgc_ptr::iterator(mem_location, mem_location + arr_size, mem_location);
}

template<class T, int size>
typename sgc_ptr<T, size>::iterator sgc_ptr<T, size>::end() {
    int arr_size;
    if (is_array) arr_size = array_size;
    else arr_size = 1;
    return sgc_ptr::iterator(mem_location, mem_location + arr_size, mem_location + arr_size);
}

template<class T, int size>
unsigned sgc_ptr<T, size>::get_gc_list_size() {
    return gc_list.size();
}

template<class T, int size>
void sgc_ptr<T, size>::show_list() {
    std::cout << "gc_list<" << typeid(T).name() << ", " << size << "> \n";
    std::cout << "mem_ptr\t\trefcount\n";
    if (gc_list.empty()) {
        std::cout << "----------EMPTY----------\n";
        return;
    }
    for (const auto &info : gc_list) {
        std::cout << "[ " << info.get_mem_location() << "\t\t" << info.get_ref_count() << " ]\n";
    }
}

template<class T, int size>
void sgc_ptr<T, size>::clear_gc_list() {
#ifdef DEBUG_SGC_PTR
    std::cout << "Before Collecting :";
    show_list();
#endif
    /*Setting all the ref_counts to Zero.*/
    for (auto &info : gc_list) {
        info.set_ref_count(0);
    }
    collect();
#ifdef DEBUG_SGC_PTR
    std::cout << "After Collecting :";
    show_list();
#endif
}