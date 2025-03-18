#include <string.h>

#include "meta.h"

MetaCommandStatus process_meta_command(InputBuffer* inputBuffer) {
    if (strcmp(inputBuffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
      } else {
        return META_COMMAND_INVALID;
    }
}
