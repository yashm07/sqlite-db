#include "node.h"

uint32_t* get_leaf_node_num_cells(void* node) {
    return node + LEAF_NODE_NUM_CELLS_OFFSET;
}

void* get_leaf_node_cell(void* node, uint32_t cellNum) {
    return node + LEAF_NODE_HEADER_SIZE + cellNum * LEAF_NODE_CELL_SIZE;
}

uint32_t* get_leaf_node_key(void* node, uint32_t cellNum) {
    return get_leaf_node_cell(node, cellNum);
}

void* get_leaf_node_value(void* node, uint32_t cellNum) {
    return get_leaf_node_cell(node, cellNum) + LEAF_NODE_KEY_SIZE;
}

void init_leaf_node(void* node) {
    *get_leaf_node_num_cells(node) = 0;
}