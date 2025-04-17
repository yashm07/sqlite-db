#include "node.h"

NodeType get_node_type(void* node) {
    uint8_t type_val = *((uint8_t*)(node + NODE_TYPE_OFFSET));

    return (NodeType)type_val;
};

void set_node_type(void* node, NodeType node_type) {
    uint8_t val = node_type;

    *((uint8_t*)(node + NODE_TYPE_OFFSET)) = val;
};

bool is_node_root(void* node) {
    uint8_t val = *((uint8_t*)(node + IS_ROOT_OFFSET));

    return (bool)val;
};

void set_node_root_field(void* node, bool is_root) {
    uint8_t val = is_root;
    
    *((uint8_t*)(node + IS_ROOT_OFFSET)) = val;
};

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
    set_node_root_field(node, false);
    set_node_type(node, LEAF_NODE);
}

void init_internal_node(void* node) {
    *get_internal_node_num_keys(node) = 0;
    set_node_root_field(node, false);
    set_node_type(node, INTERNAL_NODE);
}

uint32_t* get_internal_node_num_keys(void* node) {
    return node + INTERNAL_NODE_NUM_KEYS_OFFSET;
};

uint32_t* get_internal_node_right_child(void* node) {
    return node + INTERNAL_NODE_RIGHT_CHILD_OFFSET;
};

uint32_t* get_internal_node_cell(void* node, uint32_t cellNum) {
    return node + INTERNAL_NODE_HEADER_SIZE + cellNum * INTERNAL_NODE_CELL_SIZE;
};

uint32_t* get_internal_node_child(void* node, uint32_t childNum) {
    uint32_t num_keys = *get_internal_node_num_keys(node);

    if (childNum == num_keys) {
        return get_internal_node_right_child(node);
    } else {
        return get_internal_node_cell(node, childNum);
    }
};

uint32_t* get_internal_node_key(void* node, uint32_t keyNum) {
    return get_internal_node_cell(node, keyNum) + INTERNAL_NODE_CHILD_SIZE;
}

uint32_t get_max_key(void* node) {
    switch (get_node_type(node)) {
        case INTERNAL_NODE:
            return *get_internal_node_key(node, *get_internal_node_num_keys(node)-1);
        case LEAF_NODE:
            return *get_leaf_node_key(node, *get_leaf_node_num_cells(node)-1);
    }
}