#pragma once

#include <stdbool.h>
#include <stdint.h>


#define MAX_IDENT_SIZE 32
// only ints

enum {
    NONE            = 0,

    IDENTIFIER      = 256,
    NUMBER          = 257,

    END_OPERATOR    = 1024,
};

static char* lang_words[] = {
    (char*)"PI",
    (char*)"E",
};

typedef struct {
    uint32_t id;
    uint32_t parameter;

    uint32_t l0;
    uint32_t c0;

    uint32_t l1;
    uint32_t c1;

    uint8_t* ident;
} token_t;

bool set_source_file(char* path);
void close_source_file(void);

token_t lex_read_next(void);
token_t lex_peek_next(void);

void print_error_from_token(char* error, token_t token);
