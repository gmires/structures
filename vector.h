#ifndef __XVECTOR_H__
#define __XVECTOR_H__    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lib_xvector_malloc malloc
#define lib_xvector_free free
#define lib_xvector_realloc realloc
#define lib_xvector_memmove memmove
#define lib_xvector_memcpy memcpy

typedef struct meta_xvector_t {
    size_t size;
    size_t capacity;
} meta_xvector_t;

#define xvector_vect_to_base(vec) \
    (&((meta_xvector_t *)(void *)(vec))[-1])

#define xvector_base_to_vect(vec) \
    ((void *)&((meta_xvector_t *)(vec))[1])

#define xvector_vector_type(type) type*

#define xvector(type) xvector_vector_type(type) 

#define xvector_capacity(vec) \
    ((vec) ? (xvector_vect_to_base(vec)->capacity) : (size_t)0)

#define xvector_size(vec) \
    ((vec) ? (xvector_vect_to_base(vec)->size) : (size_t)0)

#define xvector_empty(vec) \
    (xvector_size(vec) == 0)

#define xvector_set_capacity(vec, _capacity) \
    do { \
        if(vec){ \
            xvector_vect_to_base(vec)->capacity = _capacity; \
        } \
    } while (0)

#define xvector_set_size(vec, _size) \
    do { \
        if(vec){ \
            xvector_vect_to_base(vec)->size = _size; \
        } \
    } while (0)    

#define xvector_grow(vec, _new_capacity) \
    do { \
        const size_t xv_grow_size__ = (_new_capacity) * sizeof(*(vec)) + sizeof(meta_xvector_t); \
        if (vec){ \
            const *xv_grow_ptr1__ = xvector_vect_to_base(vec); \
            const *xv_grow_ptr2__ = lib_xvector_realloc(xv_grow_ptr1__, xv_grow_size__); \
            (vec) = xvector_base_to_vect(xv_grow_ptr2__); \
        } else { \
            const *xv_grow_ptr__ = lib_xvector_malloc(xv_grow_size__); \
            (vec) = xvector_base_to_vect(xv_grow_ptr__); \
            xvector_set_size(vec, 0); \
        } \
        xvector_set_capacity((vec), (_new_capacity)); \
    } while (0)

#define xvector_next_grow(size) \
    ((size) ? (size << 1) : 1)

#define xvector_push_back(vec, value) \
    do { \
        size_t xv_push_back_cap__ = xvector_capacity(vec); \
        if (xvector_size(vec) >= xv_push_back_cap__) { \
            xvector_grow((vec), xvector_next_grow(xv_push_back_cap__)); \
        } \
        (vec)[xvector_size(vec)] = (value); \
        xvector_set_size((vec), xvector_size(vec) + 1); \
    } while (0)

#define xvector_pop_back(vec) \
    xvector_set_size((vec), xvector_size(vec) - 1)

#define xvector_last(vec) \
    ((vec) ? (xvector_size(vec) > 0 ? (vec)[xvector_size(vec) - 1] : NULL) : NULL)

#define xvector_first(vec) \
    ((vec) ? (xvector_size(vec) > 0 ? (vec)[0] : NULL) : NULL)

#define xvector_insert(vec, pos, value) \
    do { \
        size_t xv_pop_back_cap__ = xvector_capacity(vec); \
        if (xv_pop_back_cap__ <= xvector_size(vec) ){ \
            xvector_grow((vec), xvector_next_grow(xv_pop_back_cap__)); \
        } \
        if ((pos) < xvector_size(vec)) { \
            lib_xvector_memmove((vec) + (pos) + 1, (vec) + (pos), (xvector_size(vec) - (pos)) * sizeof(*(vec))); \
        } \
        (vec)[(pos)] = (value); \
        xvector_set_size((vec), xvector_size(vec) + 1); \
    } while (0)

#define xvector_free(vec) \
    do { \
        if (vec) { \
            lib_xvector_free(xvector_vect_to_base(vec)); \
            (vec) = NULL; \
        } \
    } while (0)

  #define xvector_at(vec, pos) \
    ((vec) ? (((int)(pos) < 0  || (size_t)(pos) >= xvector_size(vec)) ? NULL : (vec)[pos]) : NULL)

#endif