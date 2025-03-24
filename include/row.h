#pragma once

#define USERNAME_LENGTH 32
#define EMAIL_LENGTH 255
#define NUM_ARGS 3

#include <stdlib.h>
#include <stdio.h>

#define size_of_attribute(ptr, member) sizeof(((ptr*)0)->member)

#define ID_SIZE size_of_attribute(Row, id)
#define USERNAME_SIZE size_of_attribute(Row, username)
#define EMAIL_SIZE size_of_attribute(Row, email)
#define ID_OFFSET 0
#define USERNAME_OFFSET ID_OFFSET + ID_SIZE
#define EMAIL_OFFSET USERNAME_OFFSET + USERNAME_SIZE
#define ROW_SIZE ID_SIZE + USERNAME_SIZE + EMAIL_SIZE

/**
 * @brief Stores all fields of database row.
 */
typedef struct {
    uint32_t id;
    char username[USERNAME_LENGTH];
    char email[EMAIL_LENGTH];
} Row;


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


/**
 * @brief Prints all attributes of row
 *
 * @param Row* row
 */
void print_row(Row* row);