#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "statement.h"
#include "row.h"

StatementStatus identify_statement(InputBuffer* inputBuffer, Statement* statement) {
    if (strncmp(inputBuffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;

        uint8_t numArgs = sscanf(
            inputBuffer->buffer, "insert %d %s %s", 
            &(statement->data.id),
            statement->data.username,
            statement->data.email
        );

        if (numArgs < NUM_ARGS) {
            return STATEMENT_INVALID;
        }
        

        return STATEMENT_SUCCESS;
    }

    if (strcmp(inputBuffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return STATEMENT_SUCCESS;
    }

    return STATEMENT_INVALID;
};

StatementExecutionStatus process_statement(Statement* statement, Table* table) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            return insert(statement, table);
        case (STATEMENT_SELECT):
            return select(table);
    }
}

StatementExecutionStatus insert(Statement* statement, Table* table) {
    if (table->numRows > TABLE_MAX_ROWS) {
        return STATEMENT_EXECUTION_TABLE_FULL;
    }

    Row* row_to_insert = &(statement->data);
    serialize_row(row_to_insert, get_row_address(table, table->numRows));
    table->numRows += 1;

    return STATEMENT_EXECUTION_SUCCESS;
}

StatementExecutionStatus select(Table* table) {
    Row row;

    for (u_int32_t i = 0; i < table->numRows; i++) {
        deserialize_row(get_row_address(table, i), &row);
        print_row(&row);
    }

    return STATEMENT_EXECUTION_SUCCESS;
}