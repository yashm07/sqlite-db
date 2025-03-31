#include "table.h"
#include "row.h"

Table* create_table() {
    Table* table = (Table*)malloc(sizeof(Table));
    table->numRows = 0;

    for (uint32_t i = 0; i < PAGES_PER_TABLE; i++) {
        table->pages[i] = NULL;
    }

    return table;
};

void free_table(Table* table) {
    for(uint32_t i = 0; i < PAGES_PER_TABLE; i++) {
        free(table->pages[i]);
    }

    free(table);
};

void* get_row_address(Table* table, uint32_t rowNum) {
    uint32_t pageNum = rowNum / ROWS_PER_PAGE;
    void* page = table->pages[pageNum];

    if (page == NULL) {
        table->pages[pageNum] = malloc(PAGE_SIZE);
    }

    uint32_t rowOffset = rowNum % ROWS_PER_PAGE;
    uint32_t rowByteOffset = rowOffset * ROW_SIZE;

    return table->pages[pageNum] + rowByteOffset;
}