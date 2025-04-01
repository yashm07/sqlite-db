#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "io.h"
#include "table.h"

/**
 * @brief Represents output statuses for meta command.
 */
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_INVALID
} MetaCommandStatus;


/**
 * @brief Processes meta command.
 *
 * @param inputBuffer meta command in input buffer
 * @param Table* table
 * 
 * @return MetaCommandStatus enum - success or invalid.
 */
MetaCommandStatus process_meta_command(InputBuffer* inputBuffer, Table* table);