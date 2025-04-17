#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "statement.h"
#include "cursor.h"
#include "node.h"

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
    void *node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *(get_leaf_node_num_cells(node));

    Row* row_to_insert = &(statement->data);

    uint32_t key_to_insert = row_to_insert->id;
    Cursor* cursor = table_find(table, key_to_insert);

    if (cursor->cell_num < num_cells) {
        uint32_t key = *get_leaf_node_key(node, cursor->cell_num);

        if (key == key_to_insert) {
            return STATEMENT_EXECUTION_DUPLICATE_KEY;
        }
    }

    insert_leaf_node(cursor, row_to_insert->id, row_to_insert);
    free(cursor);

    return STATEMENT_EXECUTION_SUCCESS;
}

StatementExecutionStatus select_all(Table* table) {
    Cursor* cursor = table_start(table);
    Row row;

    while (!(cursor->end_of_table)) {
        void* rowAddr = get_cursor_value(cursor);
        deserialize_row(rowAddr, &row);
        print_row(&row);

        cursor_advance(cursor);
    }

    free(cursor);

    return STATEMENT_EXECUTION_SUCCESS;
}