#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "table.h"

/**
 * @brief Simulates opening database connection - opens database file.
 *
 * @param const char* filename
 * 
 * @return Table*
 */
Table* open_db_connection(const char* filename);

/**
 * @brief Simulates closing database connection - closes database file.
 * Frees all dynamically allocated memory.
 *
 * @param Table* table
 */
void close_db_connection(Table* table);