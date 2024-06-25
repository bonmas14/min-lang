#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lexer.h"


int main(int argc, char** argv) {
    if (argc <= 1) {
        puts("mlc {file}");
        exit(0);
    }

    set_source_file(argv[1]);

    while (1) {
        token_t tok = lex_read_next();
    

        switch (tok.id) {
            case END_OPERATOR:
            case NONE:
                printf("\n");
                return 0;
            case NUMBER:
                printf("%d ", tok.parameter);
                break;
            case IDENTIFIER:
                printf("%s ", tok.ident);
                break;
            default:
                printf("%c ", tok.id);
                break;
        }
    }
}

