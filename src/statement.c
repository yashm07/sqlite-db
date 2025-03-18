#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "statement.h"

StatementStatus identify_statement(InputBuffer* inputBuffer, Statement* statement) {
    if (strncmp(inputBuffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return STATEMENT_SUCCESS;
    }

    if (strcmp(inputBuffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return STATEMENT_SUCCESS;
    }

    return STATEMENT_INVALID;
};

void process_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("insert stuff. \n");
            break;
        case (STATEMENT_SELECT):
            printf("select stuff. \n");
            break;
    }
}