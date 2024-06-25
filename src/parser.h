#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "lexer.h"

enum {
    EXPR,
    TERM,
};

typedef struct ast_tree_t {
    uint32_t type;
    
    //bool in_parenthesis;
    token_t token;

    struct ast_tree_t* left;
    struct ast_tree_t* right;
} ast_tree_t;

ast_tree_t* parse(void);
