#include <stdbool.h>

#include "cursor.h"

Cursor* table_start(Table* table) {
    Cursor* cursor = malloc(sizeof(Cursor));

    cursor->table = table;
    cursor->row_num = 0;
    cursor->end_of_table = (table->numRows == 0);

    return cursor;
};

Cursor* table_end(Table* table) {
    Cursor* cursor = malloc(sizeof(Cursor));

    cursor->table = table;
    cursor->row_num = table->numRows;
    cursor->end_of_table = true;

    return cursor;
};

void* get_row_address(Cursor* cursor) {
    uint32_t rowNum = cursor->row_num;
    uint32_t pageNum = rowNum / ROWS_PER_PAGE;
    void* page = get_page(cursor->table->pager, pageNum);

    uint32_t rowOffset = rowNum % ROWS_PER_PAGE;
    uint32_t rowByteOffset = rowOffset * ROW_SIZE;

    return page + rowByteOffset;
}

void cursor_advance(Cursor* cursor) {
    cursor->row_num += 1;

    if (cursor->row_num >= cursor->table->numRows) {
        cursor->end_of_table = true;
    }
};