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
    uint32_t page_num;   
    uint32_t cell_num;   
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
 * @brief Moves cursor to location dependant on key value.
 *
 * @param Table* table pointer
 * @param uint32_t key
 * 
 * @return Cursor* cursor at table end.
 */
Cursor* table_find(Table* table, uint32_t key);

/**
 * @brief Gets row address. If page not created, allocate memory.
 *
 * @param Cursor* cursor
 * 
 * @return row address
 */
void* get_cursor_value(Cursor* cursor);

/**
 * @brief Moves cursor up 1.
 *
 * @param Cursor* cursor
 */
void cursor_advance(Cursor* cursor);

/**
 * @brief Insert leaf node.
 *
 * @param Cursor* cursor
 * @param uint32_t key
 * @param Row* row
 */
void insert_leaf_node(Cursor* cursor, uint32_t key, Row* row);

/**
 * @brief Insert leaf node.
 *
 * @param Table* table
 * @param uint32_t page_num
 * @param uint32_t key
 * 
 * @return Cursor* location of where key in leaf node
 */
Cursor* find_cell_leaf_node(Table* table, uint32_t page_num, uint32_t key);

