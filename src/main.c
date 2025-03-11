#include <stdio.h>
#include <string.h>

#include "io.h"

int main() {
    InputBuffer* inputBuffer = createInputBuffer();
    
    while (1) {
        printDefaultPrompt();
        readInput(inputBuffer);

        if (strcmp(inputBuffer->buffer, "exit") == 0) {
            closeInputBuffer(inputBuffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("yay!\n");
        }
    }
}



