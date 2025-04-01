#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cursor.h"
#include "statement.h"
#include "row.h"

StatementStatus identify_statement(InputBuffer* inputBuffer, Statement* statement) {
    char* keyword = strtok(inputBuffer->buffer, " ");
    
    if (strcmp(keyword, "insert") == 0) {
        statement->type = STATEMENT_INSERT;
        
        
        char* idStr = strtok(NULL, " ");
        char* username = strtok(NULL, " ");
        char* email = strtok(NULL, " ");

        if (idStr == NULL || username == NULL || email == NULL) {
            return STATEMENT_INVALID;
        }

        if (strlen(username) > USERNAME_LENGTH || strlen(email) > EMAIL_LENGTH) {
            return STRINGS_TOO_LONG;
        }

        int id = atoi(idStr);

        if (id < 0) {
            return NEGATIVE_ID;
        }

        statement->data.id = id;
        strcpy(statement->data.username, username);
        strcpy(statement->data.email, email);

        return STATEMENT_SUCCESS;
    }

    if (strcmp(keyword, "select") == 0) {
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
            return select_all(table);
    }
}

StatementExecutionStatus insert(Statement* statement, Table* table) {
    if (table->numRows > TABLE_MAX_ROWS) {
        return STATEMENT_EXECUTION_TABLE_FULL;
    }

    Row* row_to_insert = &(statement->data);
    Cursor* cursor = table_end(table);

    serialize_row(row_to_insert, get_row_address(cursor));
    table->numRows += 1;

    free(cursor);

    return STATEMENT_EXECUTION_SUCCESS;
}

StatementExecutionStatus select_all(Table* table) {
    Cursor* cursor = table_start(table);
    Row row;

    while (!(cursor->end_of_table)) {
        Row* rowAddr = get_row_address(cursor);
        deserialize_row(rowAddr, &row);
        print_row(&row);

        cursor_advance(cursor);
    }

    free(cursor);

    return STATEMENT_EXECUTION_SUCCESS;
}