#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h> // malloc
#include <string.h> // memcpy

#define VECTOR_CAPACITY(name) name ## _capacity
#define _VECTOR_DATAP(name) name ## _data
#define _VECTOR_TAIL(name) name ## _len
#define _VECTOR_TEMPP(name) name ## _temp
#define _VECTOR_TYPE(name) name ## _t

#define _VECTOR_MALLOC_LEN(name, bytes) (_VECTOR_TYPE(name) *)malloc(bytes)

#define VECTOR_CONSTRUCT(name, type_t) \
    typedef type_t _VECTOR_TYPE(name); \
    unsigned long VECTOR_CAPACITY(name) = 8; \
    unsigned long _VECTOR_TAIL(name) = 0; \
    _VECTOR_TYPE(name) *_VECTOR_DATAP(name) = _VECTOR_MALLOC_LEN(name, sizeof(_VECTOR_TYPE(name)) * _VECTOR_TAIL(name))


#define VECTOR_RESERVE(name, capacity) { \
    _VECTOR_TYPE(name) *_VECTOR_TEMPP(name) = _VECTOR_MALLOC_LEN(name, sizeof(_VECTOR_TYPE(name)) * capacity); \
    memcpy(_VECTOR_TEMPP(name), _VECTOR_DATAP(name), VECTOR_CAPACITY(name)); \
    free(_VECTOR_DATAP(name)); \
    _VECTOR_DATAP(name) = _VECTOR_TEMPP(name); \
    VECTOR_CAPACITY(name) = capacity; \
}

#define _VECTOR_AUTORESERVE(name) \
    VECTOR_RESERVE(name, (VECTOR_CAPACITY(name) * 2))


#define VECTOR_APPEND(name, data) \
    if (_VECTOR_TAIL(name) == VECTOR_CAPACITY(name)) \
        _VECTOR_AUTORESERVE(name); \
    _VECTOR_DATAP(name)[_VECTOR_TAIL(name)++] = data


#define _VECTOR_SAFE_INDEX(name, index) ( \
        index > _VECTOR_TAIL(name) \
        ? index % _VECTOR_TAIL(name) \
        : ( \
            index < 0 \
            ? _VECTOR_TAIL(name) - (-1 * index % _VECTOR_TAIL(name)) \
            : index \
        ) \
    )

#define VECTOR_AT(name, index) \
    _VECTOR_DATAP(name)[_VECTOR_SAFE_INDEX(name, index)]

#define VECTOR_BEGIN(name) VECTOR_AT(name, 0)

#define VECTOR_END(name) VECTOR_AT(name, -1)

#define VECTOR_LEN(name) _VECTOR_TAIL(name) + 1

#endif // VECTOR_H