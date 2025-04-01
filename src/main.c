#include <stdio.h>
#include <string.h>

#include "connection.h"
#include "meta.h"
#include "statement.h"

int main(int argc, char* argv[]) {
    InputBuffer* inputBuffer = createInputBuffer();

    if (argc < 2) {
        printf("error: must provide database file. \n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];
    Table* table = open_db_connection(filename);
    
    while (1) {
        printDefaultPrompt();
        readInput(inputBuffer);

        if (inputBuffer->buffer[0] == '.') {
            switch (process_meta_command(inputBuffer, table)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_INVALID):
                    printf("Invalid meta command '%s' \n", inputBuffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (identify_statement(inputBuffer, &statement)) {
            case (STATEMENT_SUCCESS):
                break;
            case (STATEMENT_INVALID):
                printf("Invalid statement '%s' \n", inputBuffer->buffer);
                continue;
            case (STRINGS_TOO_LONG):
                printf("String is too long. '%s' \n", inputBuffer->buffer);
                continue;
            case (NEGATIVE_ID):
                printf("ID is negative. '%s' \n", inputBuffer->buffer);
                continue;
        }

        switch (process_statement(&statement, table)) {
            case (STATEMENT_EXECUTION_SUCCESS):
                printf("completed.\n");
                break;
            case (STATEMENT_EXECUTION_TABLE_FULL):
                printf("incomplete. table is full.\n");
                break;
            case (STATEMENT_EXECUTION_ERROR):
                printf("incomplete. ran into error.\n");
                break;
        }
    }

    closeInputBuffer(inputBuffer);
}