#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "row.h"

void serialize_row(Row* source, void* dest) {
    memcpy(dest + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(dest + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(dest + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* dest) {
    memcpy(&(dest->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(dest->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(dest->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void print_row(Row* row) {
    printf("%d, %s, %s\n", row->id, row->username, row->email);
};

