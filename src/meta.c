#include <string.h>

#include "connection.h"
#include "meta.h"
#include "node.h"

MetaCommandStatus process_meta_command(InputBuffer* inputBuffer, Table* table) {
    if (strcmp(inputBuffer->buffer, ".exit") == 0) {
        close_db_connection(table);
        exit(EXIT_SUCCESS);
    } 
    // assuming single node tree for now
    else if (strcmp(inputBuffer->buffer, ".print_tree") == 0) {
      void* node = get_page(table->pager, 0);
      print_leaf_node(node);
    }
      else {
        return META_COMMAND_INVALID;
    }

    return META_COMMAND_SUCCESS;
}

void print_leaf_node(void* node) {
  uint32_t numCells = *get_leaf_node_num_cells(node);

  for (uint32_t i = 0; i < numCells; i++) {
    uint32_t key = *get_leaf_node_key(node, i);

    printf(" - %d: %d\n", i, key);
  }
};