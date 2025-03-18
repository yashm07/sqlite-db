#include <stdio.h>
#include <string.h>

#include "io.h"
#include "meta.h"
#include "statement.h"

int main() {
    InputBuffer* inputBuffer = createInputBuffer();
    
    while (1) {
        printDefaultPrompt();
        readInput(inputBuffer);

        if (inputBuffer->buffer[0] == '.') {
            switch (process_meta_command(inputBuffer)) {
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
        }

        process_statement(&statement);
    }

    closeInputBuffer(inputBuffer);
}