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

#ifndef MAZ_H
#define MAZ_H

#define MAZ_ASSERT assert
#define MAZ_REALLOC realloc

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


typedef enum {
    MAZ_INFO,
    MAZ_WARN,
    MAZ_ERROR,
}maz_log_level;

#define DA_INIT_CAPACITY 4
#define maz_da_append(da, item) \
    do { \
        if((da)->count >= (da)->capacity){\
            (da)->capacity = (da)->capacity == 0? DA_INIT_CAPACITY : (da)->capacity*2;\
            (da)->items = MAZ_REALLOC((da)->items, sizeof(*(da)->items) * (da)->capacity);\
            MAZ_ASSERT((da)->items);\
        }\
        (da)->items[(da)->count++] = item;\
    } while (0)

#define maz_da_append_many(da, new_itms, new_items_count)\
    do{\
        if((da)->count + new_items_count >= (da)->capacity){\
            (da)->capacity = (da)->capacity == 0? DA_INIT_CAPACITY : (da)->capacity*2;\
            while((da)->capacity < (da)->count + new_items_count){\
                (da)->capacity *= 2;\
            }\
            (da)->items = MAZ_REALLOC((da)->items, sizeof(*(da)->items) * (da)->capacity);\
            MAZ_ASSERT((da)->items);\
        }\
        memcpy((da)->items + (da)->count, new_items, sizeof(*(da)->items) * new_items_count);\
        (da)->count += new_items_count;\
    }while(0)

#define maz_da_remove_item(da, item) \
    do{\
        for(int i = 0; i < (da)->count; i++){\
            if((da)->items[i] == item){\
                (da)->items[i] = (da)->items[(da)->count - 1];\
                for(int j = i; j < (da)->count - 1; j++){\
                    (da)->items[j] = (da)->items[j + 1];\
                }\
                (da)->count--;\
                break;\
            }\
        }\
    }while(0)

#define maz_da_remove_index(da, index) \
    do {\
        if((index) < (da)->count){\
            (da)->items[(index)] = (da)->items[--(da)->count];\
        }\
    }while(0)


void maz_log(maz_log_level level, const char* fmt, ...);

#endif // !MAZ_H

// #define MAZ_IMPLEMENTATION

#ifdef MAZ_IMPLEMENTATION


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
