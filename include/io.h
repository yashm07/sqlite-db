#pragma once

#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Represents buffer to store input.
 */
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;


/**
 * @brief Creates input buffer.
 *
 * @return Pointer to InputBuffer.
 */
InputBuffer* createInputBuffer();

/**
 * @brief Reads user input.
 *
 * @return Stores input in InputBuffer struct.
 */
void readInput(InputBuffer* inputBuffer);

/**
 * @brief Default prompt.
 *
 * @return Default prompt from computer.
 */
void printDefaultPrompt();

/**
 * @brief Close input buffer.
 * 
 * Frees buffer heap memory.
 * 
 * @return void
 */
void closeInputBuffer(InputBuffer* inputBuffer);