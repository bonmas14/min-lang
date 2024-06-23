#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dynamic_array.h"

#define DYN_ARRAY_SIZE 10000

typedef struct {
    uint8_t type;
    uint32_t count;
} token_t;

bool read_program(dyn_t* file_array, char* file_path);

int main(int argc, char** argv) {
    if (argc <= 1) {
        puts("mlc {file}");
        exit(0);
    }

    dyn_t file_array = { 0 };
    if (!read_program(&file_array, argv[1]))
        exit(0);

    size_t i = 0;

    while (i < file_array.length) {
        putc(((int32_t*)file_array.data_pointer)[i++], stdout);
    }

    free(file_array.data_pointer);
}

bool read_program(dyn_t* file_array, char* file_path) {
    FILE* current_file = fopen(file_path, "r");

    if (current_file == NULL) {
        printf("cant find file %s\n", file_path);
        return false;
    }

    if (!dyn_init(&file_array, sizeof(int32_t), DYN_ARRAY_SIZE)) {
        printf("dynamic array init error\n");
        return false;
    }

    size_t i = 0;

    while (1) {
        int c = fgetc(current_file);
        if (c == -1) break; 

        int32_t* array = file_array->data_pointer;
        
        array[i] = c;

        if (i >= file_array->length) {
            if (!dyn_add_size(file_array, DYN_ARRAY_SIZE / 10)) {
                puts("error adding size");
                fclose(current_file);
                return false;
            }
        }

        i++;
    }

    fclose(current_file);

    return true;
}
