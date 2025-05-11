
void cv_create(Vector *vector, u_int32_t size) {
    vector->data = malloc(size * start_size);
    vector->type_size = size;
    vector->allocated_size = 2;
    vector->size = 0;
}

void cv_set_size(Vector *vector, uint32_t size) {
    void* new_data_section = realloc(vector->data, vector->allocated_size * size * vector->type_size);
    if (new_data_section) {
        vector->data = new_data_section;
        vector->allocated_size = size;
    } else {
        fprintf(stderr, "Error! Memory hasn't allocated!");
    }
}

void cv_add_element_(Vector *vector, void *element) {
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

void cv_delete(Vector *vector) {
    free(vector->data);
}

void cv_pop_back(Vector *vector) {
    if (vector->size > 0) {
        vector->size--;
        memset(vector->data + vector->size * vector->type_size, 0, vector->type_size);
    }
}

void cv_erase(Vector *vector, uint32_t i) {
    if (i < vector->size) {
        memcpy(vector->data + i * vector->type_size,
               vector->data + (i + 1) * vector->type_size,
               vector->type_size * (vector->size - i));
        vector->size--;
    } else {
        fprintf(stderr, "Error! Memory hasn't erased!");
    }
}

void cv_clear(Vector *vector) {
    memset(vector->data, 0, vector->size * vector->type_size);
    vector->size = 0;
}