#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef void* d_array;
static const uint8_t start_size = 2;

typedef struct Vector {
    uint32_t type_size;
    uint32_t size;
    uint32_t allocated_size;
    d_array data;
} Vector;

static void cv_create(Vector *vector, u_int32_t size);
static void cv_delete(Vector *vector);
static void cv_add_element_(Vector *vector, void *element);
static void cv_set_size(Vector *vector, uint32_t size);
static void cv_pop_back(Vector *vector);
static void cv_erase(Vector *vector, uint32_t i);
static void cv_clear(Vector *vector);

#define cv_get(vector, i, type)            *(((type*)(vector.data) + i))
#define cv_set(vector, i, type, value)     *(((type*)(vector.data) + i)) = value
#define cv_push_back(vector, type, b)        \
        {                                    \
            type temp = b;                   \
            cv_add_element_(vector, &temp);  \
        }                                    \

#include "cvector_funcs.h"