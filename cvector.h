#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const uint32_t VECTOR_INIT_SIZE = 2;

typedef struct Vector {
    uint32_t type_size;
    uint32_t size;
    uint32_t allocated_size;
    void* data;
} Vector;

static void cv_create(Vector *vector, uint32_t size);
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
        }


/*--------------------------------IMPLEMENTATION--------------------------------*/

static void cv_create(Vector *vector, uint32_t size) {
    vector->data = malloc(size * VECTOR_INIT_SIZE);
    vector->type_size = size;
    vector->allocated_size = VECTOR_INIT_SIZE;
    vector->size = 0;
}

static void cv_set_size(Vector *vector, uint32_t size) {
    void* new_data_section = realloc(vector->data, vector->allocated_size * size * vector->type_size);
    if (new_data_section) {
        vector->data = new_data_section;
        vector->allocated_size = size;
    } else {
        fprintf(stderr, "Error! Memory hasn't allocated!");
    }
}

static void cv_add_element_(Vector *vector, void *element) {
    if (vector->size == vector->allocated_size) {
        void* new_data_section = realloc(vector->data, vector->allocated_size * 2 * vector->type_size);
        if (new_data_section) {
            vector->data = new_data_section;
            vector->allocated_size *= 2;
        } else {
            fprintf(stderr, "Error! Memory hasn't allocated!");
            return;
        }
    }
    memcpy(vector->data + vector->size * vector->type_size,
           element,
           vector->type_size);
    vector->size++;
}

static void cv_delete(Vector *vector) {
    free(vector->data);
}

static void cv_pop_back(Vector *vector) {
    if (vector->size > 0) {
        vector->size--;
        memset(vector->data + vector->size * vector->type_size, 0, vector->type_size);
    }
}

static void cv_erase(Vector *vector, uint32_t i) {
    if (i < vector->size) {
        memcpy(vector->data + i * vector->type_size,
               vector->data + (i + 1) * vector->type_size,
               vector->type_size * (vector->size - i));
        vector->size--;
    } else {
        fprintf(stderr, "Error! Memory hasn't erased!");
    }
}

static void cv_clear(Vector *vector) {
    vector->size = 0;
}