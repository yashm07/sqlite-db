#include "io.h"

InputBuffer* createInputBuffer() {
    InputBuffer* inputBuffer = malloc(sizeof(InputBuffer));

    inputBuffer->buffer = NULL;
    inputBuffer->buffer_length = 0;
    inputBuffer->input_length = 0;

    return inputBuffer;
};

void readInput(InputBuffer* inputBuffer) {
    ssize_t bytes_read = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_length), stdin);

    // skip newline char
    inputBuffer->input_length = bytes_read-1;
    inputBuffer->buffer[bytes_read-1] = 0;
}

void printDefaultPrompt() {
    printf("db -> ");
}

void closeInputBuffer(InputBuffer* inputBuffer) {
    free(inputBuffer->buffer);
    free(inputBuffer);
}