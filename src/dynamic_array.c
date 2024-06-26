// Copyright (c) 2024 bonmas14
#include "dynamic_array.h"

#include <stdlib.h>

bool dyn_init(dyn_t** array, size_t type_size, size_t init_size) {
    dyn_t* dyn = *array;

    dyn->length = 0;
    dyn->capacity = init_size;
    dyn->byte_size = type_size;
    dyn->data_pointer = calloc(init_size, type_size);

    if (dyn->data_pointer == NULL)
        return false;

    return true;
}

bool dyn_add_size(dyn_t* array, size_t append_size) {
    if ((array->length + append_size) < array->capacity) {
        array->length += append_size;
        return true;
    }

    void* new = realloc(array->data_pointer, array->byte_size * (array->capacity + append_size));

    if (new == false)
        return false;

    array->data_pointer = new;
    array->capacity += append_size;
    array->length += append_size;

    return true;
}
