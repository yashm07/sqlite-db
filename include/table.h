#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "row.h"

#define PAGES_PER_TABLE 100
#define PAGE_SIZE 4096
#define ROWS_PER_PAGE PAGE_SIZE / ROW_SIZE
#define TABLE_MAX_ROWS ROWS_PER_PAGE * PAGES_PER_TABLE

/**
 * @brief Represents Table to store pages.
 */
typedef struct {
    uint32_t numRows;
    void* pages[PAGES_PER_TABLE];
} Table;

/**
 * @brief Creates new table
 * 
 * @return Table*
 */
Table* create_table();

/**
 * @brief Frees new table
 * 
 * @param Table* table to free
 */
void free_table(Table* table);

/**
 * @brief Gets row address
 *
 * @param Table* table pointer
 * @param uint32_t row number to access
 * 
 * @return row address
 */
void* get_row_address(Table* table, uint32_t rowNum);