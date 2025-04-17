#include "connection.h"
#include "node.h"

Table* open_db_connection(const char* filename) {
    Pager* pager = create_pager(filename);

    Table* table = (Table*)malloc(sizeof(Table));
    
    table->pager = pager;
    table->root_page_num = 0;

    // new file
    if (pager->num_pages == 0) {
        void* root_node = get_page(pager, 0);
        init_leaf_node(root_node);
        set_node_root_field(root_node, true);
    }

    return table;
};

void close_db_connection(Table* table) {
    Pager* pager = table->pager;

    for (uint32_t i = 0; i < pager->num_pages; i++) {
        if (pager->pages[i] == NULL) {
            continue;
        }

        flush_page(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
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
