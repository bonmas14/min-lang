#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t length;
    size_t capacity;
    size_t byte_size;
    void* data_pointer;
} dyn_t;

bool dyn_init(dyn_t** array, size_t type_size, size_t init_size);

bool dyn_add_size(dyn_t* array, size_t append_size);

