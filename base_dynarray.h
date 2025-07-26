#ifndef BASE_DYNARRAY_H
#define BASE_DYNARRAY_H

#include "base_core.h"
#include <stdlib.h>

#define _ArrayHeader_ struct { u64 count; u64 capacity; }

//#define DYNARRAY_IMPLEMENTATION
#ifdef DYNARRAY_IMPLEMENTATION
#define _defineArray(TName, T)                                  \
    typedef struct {                                            \
        T *data;                                                \
        _ArrayHeader_;                                          \
    } TName;                                                    \
                                                                \
    void _dynArrayReserve_##TName(TName *array, u64 cap);       \
    void _dynArrayRelease_##TName(TName *array);                \
    void _dynArrayPush_##TName(TName *array, T value);          \
    T _dynArrayPop_##TName(TName *array);                       \
                                                                \
    void _dynArrayReserve_##TName(TName *array, u64 cap)        \
    {                                                           \
        array->data = (T *) malloc(sizeof(*array->data) * cap); \
        array->capacity = cap;                                  \
    }                                                           \
                                                                \
    void _dynArrayRelease_##TName(TName *array)                 \
    {                                                           \
        free(array->data);                                      \
        array->capacity = 0;                                    \
        array->count = 0;                                       \
    }                                                           \
                                                                \
    void _dynArrayPush_##TName(TName *array, T value)           \
    {                                                           \
        if (array->capacity == 0)                               \
        {                                                       \
            _dynArrayReserve_##TName(array, 2);                 \
        }                                                       \
        else if (array->count == array->capacity)               \
        {                                                       \
            array->capacity *= 2;                               \
            array->data = (T *) realloc(                        \
                array->data,                                    \
                array->capacity * sizeof(*array->data)          \
            );                                                  \
        }                                                       \
        array->data[array->count] = value;                      \
        array->count += 1;                                      \
    }                                                           \
                                                                \
    T _dynArrayPop_##TName(TName *array)                        \
    {                                                           \
        array->count -= 1;                                      \
        return array->data[array->count];                       \
    }
#else
#define _defineArray(TName, T)                                  \
    typedef struct {                                            \
        T *data;                                                \
        _ArrayHeader_;                                          \
    } TName;                                                    \
                                                                \
    void _dynArrayReserve_##TName(TName *array, u64 cap);       \
    void _dynArrayRelease_##TName(TName *array);                \
    void _dynArrayPush_##TName(TName *array, T value);          \
    T _dynArrayPop_##TName(TName *array);
#endif

_defineArray(ArrayF32, f32);
_defineArray(ArrayI32, i32);

#define dynArrayReserve(array, cap) _Generic((array),           \
        ArrayF32 *: _dynArrayReserve_ArrayF32,                  \
        ArrayI32 *: _dynArrayReserve_ArrayI32                   \
    )(array, cap)
#define dynArrayRelease(array) _Generic((array),                \
        ArrayF32 *: _dynArrayRelease_ArrayF32,                  \
        ArrayI32 *: _dynArrayRelease_ArrayI32                   \
    )(array)
#define dynArrayPush(array, value) _Generic((array),            \
        ArrayF32 *: _dynArrayPush_ArrayF32,                     \
        ArrayI32 *: _dynArrayPush_ArrayI32                      \
    )(array, value)
#define dynArrayPop(array) _Generic((array),                    \
        ArrayF32 *: _dynArrayPop_ArrayF32,                      \
        ArrayI32 *: _dynArrayPop_ArrayI32                       \
    )(array)



#endif
