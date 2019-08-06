#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h> // malloc
#include <string.h> // memcpy

/**
 * @brief get the amount of elements slots currently allocated
 */
#define VECTOR_CAPACITY(name) name ## _capacity

/**
 * internals
 */

#define _VECTOR_TYPE(name) name ## _t
#define _VECTOR_DATAP(name) name ## _datap
#define _VECTOR_TEMP(name) name ## _temp
#define _VECTOR_TAIL(name) name ## _tail

/**
 * @brief initialize a vector with defualt values
 */
#define VECTOR_CONSTRUCT(name, type_t) \
    typedef type_t _VECTOR_TYPE(name); \
    unsigned long VECTOR_CAPACITY(name) = 8; \
    unsigned long _VECTOR_TAIL(name) = 0; \
    _VECTOR_TYPE(name) *_VECTOR_DATAP(name) = (_VECTOR_TYPE(name) *)malloc(sizeof(_VECTOR_TYPE(name)) * VECTOR_CAPACITY(name))

/**
 * @brief copy constructor
 */
#define VECTOR_COPY(new_name, old_name) \
    VECTOR_CONSTRUCT(new_name, _VECTOR_TYPE(old_name)); \
    VECTOR_CAPACITY(new_name) = VECTOR_CAPACITY(old_name); \
    _VECTOR_TAIL(new_name) = _VECTOR_TAIL(old_name); \
    VECTOR_RESERVE(new_name, VECTOR_CAPACITY(old_name)); \
    for (unsigned long _VECTOR_TEMP(new_name) = 0; _VECTOR_TEMP(new_name) < _VECTOR_TAIL(new_name); _VECTOR_TEMP(new_name)++) { \
        _VECTOR_DATAP(new_name)[_VECTOR_TEMP(new_name)] = _VECTOR_DATAP(old_name)[_VECTOR_TEMP(new_name)]; \
    }

/**
 * @brief allocate capacity amount of spaces in the vector
 */
#define VECTOR_RESERVE(name, capacity) { \
    _VECTOR_TYPE(name) *_VECTOR_TEMP(name) = (_VECTOR_TYPE(name) *)realloc(_VECTOR_DATAP(name), sizeof(_VECTOR_TYPE(name)) * (capacity)); \
    _VECTOR_DATAP(name) = _VECTOR_TEMP(name); \
    VECTOR_CAPACITY(name) = capacity; \
}

/**
 * @brief internal, reserve double the current capacity
 */
#define _VECTOR_AUTORESERVE(name) { \
    VECTOR_RESERVE(name, (VECTOR_CAPACITY(name) * 2)); \
}

/**
 * @brief put an item at the end of the vector
 */
#define VECTOR_APPEND(name, data) { \
    if (_VECTOR_TAIL(name) == VECTOR_CAPACITY(name)) \
        _VECTOR_AUTORESERVE(name); \
    _VECTOR_DATAP(name)[_VECTOR_TAIL(name)++] = data; \
}

/**
 * @brief internal, ensure the index is within bounds, else mod the index to be in bounds
 */
#define _VECTOR_SAFE_INDEX(name, index) ( \
    (_VECTOR_TAIL(cool) + index) % _VECTOR_TAIL(cool) \
)

/**
 * @brief safely get the value at the specified index
 */
#define VECTOR_AT(name, index) \
    _VECTOR_DATAP(name)[_VECTOR_SAFE_INDEX(name, (index))]

/**
 * @brief get the first item in the vector
 */
#define VECTOR_BEGIN(name) VECTOR_AT(name, 0)

/**
 * @brief get the last item in the vector
 */
#define VECTOR_END(name) VECTOR_AT(name, -1)

/**
 * @brief get the length of the vector (number of used elements)
 */
#define VECTOR_LEN(name) _VECTOR_TAIL(name)

/**
 * @brief set the vector size and fill it with a value
 */
#define VECTOR_SFILL(name, capacity, value) { \
    VECTOR_RESERVE(name, capacity); \
    for (_VECTOR_TYPE(name) _VECTOR_TEMP(name) = 0; _VECTOR_TEMP(name) < VECTOR_CAPACITY(name); _VECTOR_TEMP(name)++) \
        _VECTOR_DATAP(name)[_VECTOR_TEMP(name)] = (value); \
}

#endif // VECTOR_H