#include "interp.h"


int32_t execute_tree(ast_tree_t* tree) {
    if (tree->type == TERM)
        return tree->token.parameter;

    int32_t a = execute_tree(tree->left);
    int32_t b = execute_tree(tree->right);

    switch (tree->token.id) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '/':
            return a / b;
        case '*':
            return a * b;
        default:
            return 0;
    }

    return 0;
}
