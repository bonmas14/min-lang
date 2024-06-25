#include "lexer.h"
#include "dynamic_array.h"

#include <stdio.h>
#include <stdlib.h>

#define DYN_ARRAY_SIZE 10000

bool read_program(dyn_t* file_array, char* file_path);

size_t line_counter = 0;
size_t lexer_index = 0;

dyn_t source_file = { 0 };

void close_source_file(void) {
    free(source_file.data_pointer);
}

bool set_source_file(char* path) {
    close_source_file();

    line_counter = 1;
    lexer_index = 0;

    return read_program(&source_file, path);
}

token_t lex_read_next(void) {
    int32_t* source = source_file.data_pointer;
    token_t token = { 0 };
    
    eat_token:

    switch (source[lexer_index]) {
        case EOF:
        case '\0':
            token.id = END_OPERATOR;
            break;
        case '\n':
            line_counter++;
        case ' ':
            lexer_index++;
            goto eat_token;
        case '+':
        case '-':
        case '*':
        case '/': 
        case '(':
        case ')': 
            token.id = source[lexer_index];
            lexer_index++;
            break;
        default:
            if (source[lexer_index] >= '0' && source[lexer_index] <= '9') {
                token.c0 = lexer_index;
                token.l0 = line_counter;
                token.id = NUMBER;

                while (1) {
                    if (source[lexer_index] >= '0' && source[lexer_index] <= '9')
                        token.parameter = token.parameter * 10 + source[lexer_index] - '0';
                    else break;

                    lexer_index++;
                }

                token.c1 = lexer_index;
                token.l1 = line_counter;
                break;
            } 

            if ((source[lexer_index] >= 'a' && source[lexer_index] <= 'z') || (source[lexer_index] >= 'A' && source[lexer_index] <= 'Z')) {
                token.c0 = lexer_index;
                token.l0 = line_counter;
                token.id = IDENTIFIER;

                int32_t size = MAX_IDENT_SIZE - 1;

                token.ident = malloc(sizeof(uint8_t) * MAX_IDENT_SIZE);

                if (token.ident == NULL) {
                    token.id = NONE;
                    puts("malloc error at ident init");
                    break;
                }
                for (size_t i = 0; i < MAX_IDENT_SIZE; i++) {
                    token.ident[i] = 0;
                }


                while (size-- > 0) {
                    if ((source[lexer_index] >= 'a' && source[lexer_index] <= 'z') || (source[lexer_index] >= 'A' && source[lexer_index] <= 'Z'))
                        token.ident[MAX_IDENT_SIZE - 2 - size] = source[lexer_index];
                    
                    else break;

                    lexer_index++;
                }

                token.c1 = lexer_index;
                token.l1 = line_counter;

                if ((source[lexer_index] >= 'a' && source[lexer_index] <= 'z') || (source[lexer_index] >= 'A' && source[lexer_index] <= 'Z')) {
                    puts("greater that max");
                    token.id = NONE;
                    break;
                }

                break;
            }

            lexer_index++;
            // forget about identifier right now 
            goto eat_token; break;
    }

    return token;
}

bool read_program(dyn_t* file_array, char* file_path) {
    FILE* current_file = fopen(file_path, "r");

    if (current_file == NULL) {
        printf("cant find file at \"%s\".\n", file_path);
        return false;
    }

    if (!dyn_init(&file_array, sizeof(int32_t), DYN_ARRAY_SIZE)) {
        printf("dynamic array init error.\n");
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
