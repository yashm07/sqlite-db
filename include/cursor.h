#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "table.h"

/**
 * @brief Represents database cursor.
 */
typedef struct {
    Table* table;
    uint32_t row_num;   
    // position end of table - last entry + 1
    bool end_of_table;
} Cursor;

/**
 * @brief Creates cursor at table start.
 *
 * @param Table* table pointer
 * 
 * @return Cursor* cursor at table start.
 */
Cursor* table_start(Table* table);

/**
 * @brief Creates cursor at table end.
 *
 * @param Table* table pointer
 * 
 * @return Cursor* cursor at table end.
 */
Cursor* table_end(Table* table);

/**
 * @brief Gets row address. If page not created, allocate memory.
 *
 * @param Cursor* cursor
 * 
 * @return row address
 */
void* get_row_address(Cursor* cursor);

/**
 * @brief Moves cursor up 1.
 *
 * @param Cursor* cursor
 */
void cursor_advance(Cursor* cursor);
