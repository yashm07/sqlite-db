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
        split_and_insert_leaf_node(cursor, key, row);
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

void split_and_insert_leaf_node(Cursor* cursor, uint32_t key, Row* row) {
    void* old_node = get_page(cursor->table->pager, cursor->page_num);
    
    uint32_t unused_page_num = get_unused_page_num(cursor->table->pager);
    void* new_node = get_page(cursor->table->pager, cursor->page_num);
    init_leaf_node(new_node);

    // move contents to new node, shift contents in old node down
    for (uint32_t i = LEAF_NODE_MAX_CELLS; i >= 0; i--) {
        void* destination_node;

        if (i >= LEAF_NODE_LEFT_SPLIT_COUNT) {
            destination_node = new_node;
        } else {
            destination_node = old_node;
        }

        uint32_t index_in_node = i % LEAF_NODE_LEFT_SPLIT_COUNT;
        void* destination_addr = get_leaf_node_cell(destination_node, index_in_node);

        if (i == cursor->cell_num) {
            serialize_row(row, destination_addr);
        } else if (i < cursor->cell_num) {
            memcpy(destination_addr, get_leaf_node_cell(old_node, i), LEAF_NODE_CELL_SIZE);
        } else {
            memcpy(destination_addr, get_leaf_node_cell(old_node, i-1), LEAF_NODE_CELL_SIZE);
        }
    }

    // update parent node
    if (is_node_root(old_node)) {
        create_new_root(cursor->table, unused_page_num);
    } else {
        printf("error: need to update parent logic after split.\n");
        exit(EXIT_FAILURE);
    }
};

void create_new_root(Table* table, uint32_t right_child_page_num) {
    void* root_node = get_page(table->pager, table->root_page_num);

    uint32_t left_child_page_num = get_unused_page_num(table->pager);
    void* left_child = get_page(table->pager, left_child_page_num);

    // root node contents -> left child
    memcpy(left_child, root_node, PAGE_SIZE);
    set_node_root_field(left_child, false);
    
    // set up root node
    init_internal_node(root_node);
    set_node_root_field(root_node, true);

    *get_internal_node_num_keys(root_node) = 1;
    
    // TODO: rename func to ..._left_child
    *get_internal_node_child(root_node, 0) = left_child_page_num;

    // set key val of node to be max key of left child
    uint32_t left_child_max_key = get_max_key(left_child);

    *get_internal_node_key(root_node, 0) = left_child_max_key;
    *get_internal_node_right_child(root_node) = right_child_page_num;
};