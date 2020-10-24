//
// Created by thunderfox on 17/10/20.
//

#ifndef SIMPLEGC_SGC_INFO_H
#define SIMPLEGC_SGC_INFO_H

/*
 * This class stores necessary information for garbage collection,
 * Each instance of this class will contain memory location
 * of object to which this sgc_info object is associated with,
 * and reference count for each memory location that has
 * been allocated through sgc_ptr. It will also contain information
 * that whether a ptr is array and if it is its length will also be available.
 */

template<class T>
class sgc_info {
    /*Reference Count of each sgc_ptr reference*/
    unsigned ref_count;
    /*Memory location of object*/
    T *mem_ptr;
    bool is_array;
    /*length will be 0 if pointer is not array.*/
    unsigned length;
public:
/* Constructor for sgc_info class takes in memory location
 * and size if pointer points to array of objects
 * size is a default argument if pointer is not an array
 * then default size will be zero.
 */
    explicit sgc_info(T *mem_ptr, int size = 0);

    /*Getter for ref_count*/
    unsigned int get_ref_count() const;

    /*Setter for ref_count*/
    void set_ref_count(unsigned int ref_count);

    /*operator == overloaded for STL list operations*/
    bool operator==(sgc_info other) const;
    /*Getter for is_array bool*/
    bool get_is_array() const;
};


#endif //SIMPLEGC_SGC_INFO_H
