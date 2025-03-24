#pragma once

#define size_of_attribute(ptr, member) sizeof(((ptr*)0)->member)

#define USERNAME_LENGTH 32
#define EMAIL_LENGTH 255
#define NUM_ARGS 3

#include <stdlib.h>
#include <stdio.h>

#include "io.h"

/**
 * @brief Stores all fields of database row.
 */
typedef struct {
    uint32_t id;
    char username[USERNAME_LENGTH];
    char email[EMAIL_LENGTH];
} Row;

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

/**
 * @brief Serializes row
 *
 * @param Row* row info
 * @param void* destination to store row info
 */
void serialize_row(Row* source, void* dest);

/**
 * @brief Deserializes row
 *
 * @param void* source
 * @param Row* desintation to store info
 */
void deserialize_row(void* source, Row* dest);