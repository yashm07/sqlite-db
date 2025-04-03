#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "row.h"

// leaf/internal node header fields
#define NODE_TYPE_SIZE sizeof(uint8_t)
#define NODE_TYPE_OFFSET 0
#define IS_ROOT_SIZE sizeof(uint8_t)
#define IS_ROOT_OFFSET NODE_TYPE_SIZE
#define PARENT_POINTER_SIZE sizeof(uint32_t)
#define PARENT_POINTER_OFFSET (IS_ROOT_OFFSET + IS_ROOT_SIZE)
#define COMMON_NODE_HEADER_SIZE (NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE)

// leaf node header fields
#define LEAF_NODE_NUM_CELLS_SIZE sizeof(uint32_t)
#define LEAF_NODE_NUM_CELLS_OFFSET COMMON_NODE_HEADER_SIZE
#define LEAF_NODE_HEADER_SIZE (COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE)

// leaf node data fields
#define LEAF_NODE_KEY_SIZE sizeof(uint32_t)
#define LEAF_NODE_KEY_OFFSET 0
#define LEAF_NODE_VALUE_SIZE ROW_SIZE
#define LEAF_NODE_VALUE_OFFSET (LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE)
#define LEAF_NODE_CELL_SIZE (LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE)
#define LEAF_NODE_SPACE_FOR_CELLS (PAGE_SIZE - LEAF_NODE_HEADER_SIZE)
#define LEAF_NODE_MAX_CELLS (LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE)

/**
 * @brief Enum to represent node types. 
 * Each type stores data differently.
 */
typedef enum {
    INTERNAL_NODE,
    LEAF_NODE
} NodeType;

/**
 * @brief Accesses num cells header of leaf node.
 *
 * @param void* node
 * 
 * @return uint32_t* pointer to num cells header
 */
uint32_t* get_leaf_node_num_cells(void* node);

/**
 * @brief Accesses cell of a leaf node.
 *
 * @param void* node
 * @param uint32_t cellNum
 * 
 * @return void* pointer to cell of leaf node.
 */
void* get_leaf_node_cell(void* node, uint32_t cellNum);

/**
 * @brief Accesses key of a cell of a leaf node.
 *
 * @param void* node
 * @param uint32_t cellNum
 * 
 * @return void* pointer to key of cell of leaf node.
 */
uint32_t* get_leaf_node_key(void* node, uint32_t cellNum);

/**
 * @brief Accesses value of a cell of a leaf node.
 *
 * @param void* node
 * @param uint32_t cellNum
 * 
 * @return void* pointer to value of cell of leaf node.
 */
void* get_leaf_node_value(void* node, uint32_t cellNum);

/**
 * @brief Initializes leaf node. Sets num cells to 0.
 *
 * @param void* node
 */
void init_leaf_node(void* node);

/**
 * @brief Get node type. Leaf or internal node.
 *
 * @param void* node
 * 
 * @return NodeType
 */
NodeType get_node_type(void* node);

/**
 * @brief Set node type. Leaf or internal node.
 *
 * @param void* node
 * @param NodeType node type
 */
void set_node_type(void* node, NodeType node_type);