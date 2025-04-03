#include <stdbool.h>
#include <string.h>

#include "cursor.h"
#include "node.h"

Cursor* table_start(Table* table) {
    Cursor* cursor = malloc(sizeof(Cursor));

    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->cell_num = 0;
    
    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *get_leaf_node_num_cells(root_node);

    cursor->end_of_table = (num_cells == 0);

    return cursor;
};

Cursor* table_find(Table* table, uint32_t key) {
    uint32_t root_page_num = table->root_page_num;
    void* root_node = get_page(table->pager, root_page_num);

    if (get_node_type(root_node) == LEAF_NODE) {
        return find_cell_leaf_node(table, root_page_num, key);
    } else {
        printf("internal node!");
        exit(EXIT_FAILURE);
    }
};

void* get_cursor_value(Cursor* cursor) {
    uint32_t pageNum = cursor->page_num;
    void* page = get_page(cursor->table->pager, pageNum);

    return get_leaf_node_value(page, cursor->cell_num);
}

void cursor_advance(Cursor* cursor) {
    uint32_t pageNum = cursor->page_num;
    void* node = get_page(cursor->table->pager, pageNum);

    cursor->cell_num += 1;

    if (cursor->cell_num >= (*get_leaf_node_num_cells(node))) {
        cursor->end_of_table = true;
    }
};

void insert_leaf_node(Cursor* cursor, uint32_t key, Row* row) {
    void* node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *get_leaf_node_num_cells(node);

    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        printf("error: the node is full. must split node.\n");
        exit(EXIT_FAILURE);
    }

    if (cursor->cell_num < num_cells) {
        // shift up
        for (uint32_t i = num_cells; i > cursor->cell_num; i--) {
            memcpy(get_leaf_node_cell(node, i), get_leaf_node_cell(node, i-1), LEAF_NODE_CELL_SIZE);
        }
    }

    *(get_leaf_node_num_cells(node)) += 1;
    *(get_leaf_node_key(node, cursor->cell_num)) = key;
    serialize_row(row, get_leaf_node_value(node, cursor->cell_num));
};

Cursor* find_cell_leaf_node(Table* table, uint32_t page_num, uint32_t key) {
    void* node = get_page(table->pager, page_num);
    uint32_t num_cells = *get_leaf_node_num_cells(node);

    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = page_num;

    uint32_t l = 0;
    uint32_t r = num_cells;

    while (l < r) {
        uint32_t mid_idx = (l+r)/2;
        uint32_t key_val = *get_leaf_node_key(node, mid_idx);

        if (key == key_val) {
            cursor->cell_num = mid_idx;
            return cursor;
        }

        if (key > key_val) {
            l = mid_idx + 1;   
        } else {
            r = mid_idx;
        }
    }

    cursor->cell_num = l;
    return cursor;
};
