#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "io.h"
#include "table.h"

/**
 * @brief Represents output statuses for statement.
 */
typedef enum {
    STATEMENT_SUCCESS,
    STATEMENT_INVALID,
    STRINGS_TOO_LONG,
    NEGATIVE_ID
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

typedef enum {
    STATEMENT_EXECUTION_SUCCESS,
    STATEMENT_EXECUTION_ERROR,
    STATEMENT_EXECUTION_TABLE_FULL,
} StatementExecutionStatus;

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
 * @param Table* table
 * 
 * @return StatementExecutionStatus
 */
StatementExecutionStatus process_statement(Statement* statement, Table* table);

/**
 * @brief Inserts statement info into table.
 *
 * @param Statement* statement struct with info
 * @param Table* table to insert into
 * 
 * @return StatementExecutionStatus
 */
StatementExecutionStatus insert(Statement* statement, Table* table);

/**
 * @brief SELECT * from table
 *
 * @param Table* table to insert into
 * 
 * @return StatementExecutionStatus
 */
StatementExecutionStatus select_all(Table* table);