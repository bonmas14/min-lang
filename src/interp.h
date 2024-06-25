#pragma once

#include <stdint.h>

#include "lexer.h"
#include "parser.h"

int32_t execute_tree(ast_tree_t* tree);
