//
// Created by thunderfox on 17/10/20.
//

#ifndef SIMPLEGC_SGC_PTR_H
#define SIMPLEGC_SGC_PTR_H
//Uncomment below line to log every allocation and de-allocation in console.
#define DEBUG_SGC_PTR

#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>
#include "sgc_iterator.h"
#include "sgc_info.h"

/* sgc_ptr implements a pointer type that
 * uses automatic garbage collection. sgc_ptr
 * should only be used to point memory locations
 * that were dynamically allocated using new.
 *
 * Array size should be specified when used for referring
 * an array.
 */
template<class T, int size = 0>
class sgc_ptr {
/* gc_list maintains the information about all sgc_ptrs.
 * gc_list is used to recycle memory locations with no active references.
 * gc_list is shared among objects of a particular class.
 */
    static std::list<sgc_info<T>> gc_list;
/* mem_location points to memory address
 * to which sgc_ptr currently points.
 */
    T *mem_location;
/* if sgc_ptr points to a allocated array
 * then is_array is true, else it is false.
 */
    bool is_array;
/* contains size of array if sgc_ptr points to an
 * allocated array.
 */
    unsigned array_size;
/* Indicates whether the first sgc_ptr is created
 * for a particular type.
 */
    static bool first_created;

/* Returns an iterator to sgc_info within gc_list.
 * returns end() iterator of gc_list if T_ptr is not found.
 */
    typename std::list<sgc_info<T>>::iterator find_sgc_info(T *T_ptr);

public:
/*Iterator type for sgc_ptr.*/
    typedef sgc_iterator<T> iterator;

/* sgc_ptr  constructor can be used to construct
 * initialized and uninitialized objects.
 */
    sgc_ptr(T *T_ptr = nullptr);

/* Copy constructor for sgc_ptr*/
    sgc_ptr(const sgc_ptr &other);

/* Destructor for sgc_ptr*/
    ~sgc_ptr();

/* collect() is used to free memory locations that has no active references.
 * Returns true if at least one memory location was freed.
 */
    static bool collect();

/* Overload assignment of pointer to sgc_ptr*/
    T *operator=(T *T_ptr);

/* Overload assignment of sgc_ptr to sgc_ptr*/
    sgc_ptr &operator=(sgc_ptr &other);

/* Returns a reference of object pointed by this sgc_ptr*/
    T &operator*() const;

/* Returns the address pointed by this sgc_ptr*/
    T *operator->();

/* Returns object specified by index i in []*/
    T &operator[](unsigned i) const;

/* Conversion function to T * */
    operator T *();

/* Returns the iterator to start of the memory*/
    iterator begin();

/* Returns the iterator to end of the memory*/
    iterator end();

/* Returns the size of gc_list for this type of sgc_ptr*/
    static unsigned get_gc_list_size();

/* Logs contents of gc_list in console for debug purposes.*/
    static void show_list();

/* clear_gc_list() is used to free remaining memory when
 * application exits, this solves circular reference problem.
 */
    static void clear_gc_list();

};


#endif //SIMPLEGC_SGC_PTR_H
