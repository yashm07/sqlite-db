#include "connection.h"

Table* open_db_connection(const char* filename) {
    Pager* pager = create_pager(filename);
    uint32_t numRows = pager->file_length / ROW_SIZE;

    Table* table = (Table*)malloc(sizeof(Table));
    
    table->numRows = numRows;
    table->pager = pager;

    return table;
};

void close_db_connection(Table* table) {
    Pager* pager = table->pager;
    uint32_t numFullPages = table->numRows / ROWS_PER_PAGE;

    for (uint32_t i = 0; i < numFullPages; i++) {
        if (pager->pages[i] == NULL) {
            continue;
        }

        flush_page(pager, i, PAGE_SIZE);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    uint32_t remainingRows = table->numRows % ROWS_PER_PAGE;

    if (remainingRows > 0) {
        uint32_t pageNum = numFullPages;

        if (pager->pages[pageNum] != NULL) {
            flush_page(pager, pageNum, remainingRows * ROW_SIZE);
            free(pager->pages[pageNum]);
            pager->pages[pageNum] = NULL;
        }
    }

    int result = close(pager->file_descriptor);

    if (result == -1) {
        printf("error: cannot close db file.\n");
        exit(EXIT_FAILURE);
    }

    // free all pages
    for (uint32_t i = 0; i < PAGES_PER_TABLE; i++) {
        void* page = pager->pages[i];

        if (page) {
            free(page);
            pager->pages[i] = NULL;
        }
    }

    free(pager);
    free(table);
};
