#include <string.h>

#include "meta.h"
#include "connection.h"

MetaCommandStatus process_meta_command(InputBuffer* inputBuffer, Table* table) {
    if (strcmp(inputBuffer->buffer, ".exit") == 0) {
        close_db_connection(table);
        exit(EXIT_SUCCESS);
      } else {
        return META_COMMAND_INVALID;
    }
}
