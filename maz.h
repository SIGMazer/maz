// TABLE OF CONTENTS
// -----------------
// 1. Table of Contents
// 2. Usage 
// 3. Documentation
//    3.1. Dynamic Arrays
//        3.1.1. Non-function interface
//        3.1.2. Functions (macros)
// 4. Credits
// 5. License
// -----------------

// USAGE
// ---------------------
// To  use this library, do this in one C file:
//      #define MAZ_IMPLEMENTATION
//      #include "maz.h"
//

// DOCUMENTATION
// -------------
// 3. Documentation
//    3.1. Dynamic Arrays
//        3.1.1. Non-function interface
// ------------------------
// Declare an empty dynamic array of type T
// T* da = NULL;

// Access the i'th item of a dynamic array 'da' of type T
// T* da:
// da[i]

//        3.1.2. Functions (macros)
// ------------------------
// maz_daput:
//   void maz_daput(T* da, T item);
//     Adds an item to the end of the dynamic array.

// maz_daget:
//   T maz_daget(T* da, size_t index);
//     Retrieves the item at the specified index in the dynamic array.

// maz_daset:
//   void maz_daset(T* da, size_t index, T item);
//     Sets the item at the specified index in the dynamic array.

// maz_dadel:
//   void maz_dadel(T* da, size_t index);
//     Deletes the item at the specified index in the dynamic array.

// maz_dadeln:
//   void maz_dadeln(T* da, size_t index, size_t size);
//     Deletes multiple items starting from the specified index in the dynamic array.

// maz_daclear:
//   void maz_daclear(T* da);
//     Clears the dynamic array (sets count to 0).

// maz_dafree:
//   void maz_dafree(T* da);
//     Frees the dynamic array.

// maz_daputat:
//   void maz_daputat(T* da, size_t index, T item);
//     Inserts an item at the specified index in the dynamic array.

// maz_daputmany:
//   void maz_daputmany(T* da, T* items, size_t size);
//     Adds multiple items to the end of the dynamic array.

// maz_damybegrow:
//   int maz_damybegrow(T* da, size_t addlen);
//     Checks and grows the dynamic array if necessary.

// maz_dagrow:
//   void maz_dagrow(T* da, size_t addlen, size_t cap);
//     Grows the dynamic array to accommodate additional elements.

// maz_damemmove:
//   void maz_damemmove(T* da, size_t dst, size_t src, size_t count);
//     Moves memory within the dynamic array.

// maz_dacpy:
//   void maz_dacpy(T* dst, T* src);
//     Copies the content of one dynamic array to another.

// maz_dancpy:
//   void maz_dancpy(T* dst, T* src, size_t n);
//     Copies a specified number of elements from one dynamic array to another.

// maz_dancpyf:
//   void* maz_dancpyf(void* da, size_t elemsize, size_t n);
//     Copies the content of one dynamic array to a new dynamic array.
// 
// maz_dadelswap:
//      void maz_dadelswap(T* da, size_t index);
//      Deletes the item at the specified index in the dynamic array and replaces it with the last item in the array.
//      This is useful when the order of the items in the array does not matter.
//      This is faster than maz_dadel O(1) performace, but the order of the items in the array is not preserved.
//

// CREDITS
// -------
// 4. Credits
// ------------------------
// Credits and acknowledgments for the code and libraries used.
//
// LICENSE
// -------
// 5. License
// ------------------------
// This software is dual-licensed to the public domain and under MIT.
// See end of file for detailed license information.


#ifndef MAZ_H
#define MAZ_H

#define MAZ_ASSERT assert
#define MAZ_REALLOC realloc
#define MAZ_FREE free

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


typedef enum {
    MAZ_INFO,
    MAZ_WARN,
    MAZ_ERROR,
} maz_log_level;

typedef struct {
    size_t count;
    size_t capacity;
    void *items;
} Maz_da_t;

#define DA_INIT_CAPACITY 4
#define da_header(da) ((Maz_da_t *)(da) -1)
#define maz_dalen(da) ((da) ? da_header(da)->count : 0)
#define maz_daput(da, item) (maz_damybegrow(da, 1), (da)[da_header(da)->count++] = (item))
#define maz_daget(da, index) ((da)[index])
#define maz_daset(da, index, item) ((da)[index] = (item))
#define maz_dadel(da, index) (maz_dadeln(da, index, 1))
#define maz_dadelswap(da, index) ((da)[index] = (da)[maz_dalen(da) - 1], da_header(da)->count--)
#define maz_dadeln(da, index, size) (maz_damemmove(da, index, index + size, maz_dalen(da) - index - size), da_header(da)->count -= size)
#define maz_daclear(da) ((da) ? da_header(da)->count = 0 : 0)
#define maz_dafree(da) ((da) ? (MAZ_FREE(da_header(da)), (da) = NULL) : 0)
#define maz_damemmove(da, dst, src, count) (memmove(&(da)[dst], &(da)[src], (count) * sizeof(*(da))))
#define maz_dacpy(dst, src) ((dst) = maz_dancpyf(src, sizeof(*(dst)), maz_dalen(src)))
#define maz_dancpy(dst, src, n) ((dst) = maz_dancpyf(src, sizeof(*(dst)), n))
#define maz_daputmany(da,items,size) (maz_damybegrow(da, size), memcpy(&(da)[da_header(da)->count], items, (size) * sizeof(*(da))), da_header(da)->count+= (size))
#define maz_daputat(da, index, item) \
    (maz_damybegrow(da, 1), maz_damemmove(da, index + 1, index, maz_dalen(da) - index), (da)[index] = (item), da_header(da)->count++)


#define maz_damybegrow(da, addlen) \
    (!(da) || da_header(da)->count + (addlen) >= da_header(da)->capacity ? \
     (maz_dagrow(da,addlen,0),0) : 0)

#define maz_dagrow(da,addlen,cap) \
    ((da) = maz_dagrowf(da, sizeof(*(da)), addlen, cap))

void maz_log(maz_log_level level, const char* fmt, ...);

#endif // !MAZ_H

// #define MAZ_IMPLEMENTATION

#ifdef MAZ_IMPLEMENTATION

void *maz_dancpyf(void *da, size_t elemsize, size_t n){
    if(da == NULL){
        return NULL;
    }
    void *cpy = MAZ_REALLOC(NULL, elemsize * n + sizeof(Maz_da_t));
    MAZ_ASSERT(cpy != NULL && "Could not allocate memory");
    cpy = (char *)cpy + sizeof(Maz_da_t);
    memcpy(cpy, da, elemsize * n);
    da_header(cpy)->count = n;
    da_header(cpy)->capacity = n;
    return cpy;
}

void *maz_dagrowf(void *da, size_t elemsize, size_t addlen, size_t mincap){
    if(da == NULL){
        mincap = (mincap > DA_INIT_CAPACITY) ? mincap : DA_INIT_CAPACITY;
        da = MAZ_REALLOC(NULL, elemsize * mincap + sizeof(Maz_da_t));
        MAZ_ASSERT(da != NULL && "Could not allocate memory");
        da = (char *)da + sizeof(Maz_da_t);
        da_header(da)->count = 0;
        da_header(da)->capacity = mincap;
        return da;
    }else{
        size_t newcap = da_header(da)->capacity + addlen;
        if(newcap < mincap){
            newcap = mincap;
        }
        da = (char *)da - sizeof(Maz_da_t);
        da = MAZ_REALLOC(da, elemsize * newcap + sizeof(Maz_da_t));
        MAZ_ASSERT(da != NULL && "Could not allocate memory");
        da = (char *)da + sizeof(Maz_da_t);
        da_header(da)->capacity = newcap;
        return da;
    }
}

void maz_log(maz_log_level level, const char *fmt, ...){
    switch (level) { 
        case MAZ_INFO: {
            fprintf(stderr, "[INFO]: ");
            break;
        }
        case MAZ_WARN: {
            fprintf(stderr, "[WARN]: ");
            break;
        }
        case MAZ_ERROR: {
            fprintf(stderr, "[ERROR]: ");
            break;
        }
        default: {
            maz_log(MAZ_ERROR, "Invalid log level");
            exit(1);
            break;
        }
    }

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

#endif // MAZ_IMPLEMENTATION

// Copyright 2023 Mazin Sayed <mazinasd7@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
