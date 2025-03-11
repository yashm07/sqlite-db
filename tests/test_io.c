#include <stdio.h>
#include <stdlib.h>
#include <cmocka.h>
#include "io.h"


static ssize_t mock_getline(char **lineptr, size_t *n, FILE *stream) {
    const char *test_input = "test input";
    size_t str_length = strlen(test_input) + 1;

    *lineptr = realloc(*lineptr, str_length);
    strcpy(*lineptr, test_input);
    *n = str_length;
    return str_length; 
}

static void test_createInputBuffer(void **state) {
    (void) state;

    InputBuffer* buffer = createInputBuffer();
    
    assert_non_null(buffer);
    assert_null(buffer->buffer);
    assert_int_equal(buffer->buffer_length, 0);
    assert_int_equal(buffer->input_length, 0);

    closeInputBuffer(buffer);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_createInputBuffer),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}