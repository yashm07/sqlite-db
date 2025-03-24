#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "io.h"
#include "row.h"

/**
 * @brief Represents output statuses for statement.
 */
typedef enum {
    STATEMENT_SUCCESS,
    STATEMENT_INVALID
} StatementStatus;

/**
 * @brief Represents statement types.
 */
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

/**
 * @brief Stores information regarding statement.
 */
typedef struct {
    StatementType type;
    Row data;
} Statement;

/**
 * @brief Identify SQL statement type. Represents how SQLite compiler parses string
 *  and outputs as bytecode.
 *
 * @param inputBuffer meta command in input buffer
 * @param Statement* statement info
 * 
 * @return StatementStatus enum - success or invalid.
 */
StatementStatus identify_statement(InputBuffer* inputBuffer, Statement* statement);

/**
 * @brief Process statement.
 *
 * @param Statement* statement info
 */
void process_statement(Statement* statement);