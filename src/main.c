#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lexer.h"
#include "parser.h"


void traverse(ast_tree_t* node, size_t deep) {
    if (node == NULL) return;

    for (size_t i = 0; i < deep; i++) {
        putc(' ', stdout);
    }

    switch (node->token.id) {
        case NUMBER:
            printf("%d", node->token.parameter);
            break;
        default:
            printf("%c", node->token.id);
            break;
    
    }

    if (node->right != NULL) {
        putc('\n', stdout);
        traverse(node->right, deep + 1);
    }

    if (node->left != NULL) {
        putc('\n', stdout);
        traverse(node->left, deep + 1);
    }
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        puts("mlc {file}");
        exit(0);
    }

    set_source_file(argv[1]);

    ast_tree_t* tree = parse();

    traverse(tree, 0);
    printf("\n");
}


