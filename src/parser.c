#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

void* safe_alloc(size_t size) {
    void* p = malloc(size);
    if (p == NULL) {
        puts("Error alloc mem");
        exit(0);
    }

    return p;
}

ast_tree_t* create_node(void) {
    ast_tree_t* node = safe_alloc(sizeof(ast_tree_t));

    node->type = 0;
    node->token = (token_t){ 0 };

    node->left = NULL;
    node->right = NULL;

    return node;
}

ast_tree_t* rotate_left(ast_tree_t* node) {
    ast_tree_t* temp = node->right;
    node->right = node->right->left;

    temp->left = node;
    return temp;
}

ast_tree_t* rotate_if_needed(ast_tree_t* node) {
    switch (node->token.id) {
        case '*': 
        case '/':
            if (node->right->token.id == '+' || node->right->token.id == '-')
                return rotate_left(node);
            break;
    }
    return node;
}

ast_tree_t* term_parse(token_t current) {
    ast_tree_t* node = create_node();

    switch (current.id) {
        case NUMBER:
            node->type = TERM; 
            node->token = current;
            break;
        default:
            free(node);
            print_error_from_token("parsing TERM, but recieving EXPR", current);
            return NULL;
            break;
    }

    return node;
}

ast_tree_t* expr_parse(token_t current) {
    ast_tree_t* node;
    
    token_t lookahead = lex_peek_next();

    switch (lookahead.id) {
        case '-': 
        case '+':
        case '*': 
        case '/':
            if (current.id == NONE) {
                print_error_from_token("wrong placement", lookahead);
                return NULL;
            }
            node = create_node(); 
            node->type = EXPR;
            node->token = lookahead;
            node->right = expr_parse(lex_read_next());
            node->left = term_parse(current); 
            node = rotate_if_needed(node);
            break;
        case NUMBER:
            return expr_parse(lex_read_next());
        case END_OPERATOR:
            return term_parse(current);
        default:
            print_error_from_token("not supporting this token", lookahead);
            return NULL;
    }
    return node;
}

ast_tree_t* parse(void) {
    return expr_parse((token_t){ 0 });
}
