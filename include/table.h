#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "row.h"

#define PAGES_PER_TABLE 100
#define PAGE_SIZE 4096
#define MAX_FILENAME_LENGTH 255
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * PAGES_PER_TABLE)

/**
 * @brief Stores all fields of Pager. Responsible for fetching memory.
 */
typedef struct {
    int file_descriptor;
    uint32_t file_length;
    void* pages[PAGES_PER_TABLE];
    char filename[MAX_FILENAME_LENGTH + 1];
} Pager;

/**
 * @brief Represents Table to store pages.
 */
typedef struct {
    uint32_t numRows;
    Pager* pager;
} Table;


/**
 * @brief Creates new pager. Opens database file and stores properties.
 *
 * @param const char* filename to read
 * 
 * @return Pager* pointer to Pager
 */
Pager* create_pager(const char* filename);

/**
 * @brief Fetch page. On cache miss, pull data from file (or disk).
 *
 * @param Pager* pager
 * @param uint32_t pageNum
 * 
 * @return Pager* pointer to Pager
 */
Pager* get_page(Pager* pager, uint32_t pageNum);

/**
 * @brief Flushes page from cache into memory (file).
 *
 * @param Pager* pager
 * @param uint32_t pageNum
 * @param uint32_t size
 */
void flush_page(Pager* pager, uint32_t pageNum, uint32_t size);