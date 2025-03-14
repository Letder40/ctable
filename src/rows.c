#include "../include/rows.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add_padding(const char* str) {
    size_t len = strlen(str);
    size_t padding_len = strlen(PADDING);
    size_t total_size = 
        len + (2 * padding_len) + 1;

    char* padded_str = (char*)malloc(total_size);

    if (!padded_str) exit(EXIT_FAILURE);

    strcpy(padded_str, PADDING);
    strcat(padded_str, str);
    strcat(padded_str, PADDING);

    return padded_str;
}

size_t rowlen(const row_t row) {
    size_t len = 0;
    while (row[len] != NULL) {
        len++;
    }

    return len;
}

row_t create_row(const row_t row) {
    size_t row_size = rowlen(row);

    row_t padded_row = malloc((row_size + 1) * sizeof(char*));

    if (!padded_row) exit(EXIT_FAILURE);

    for (size_t i = 0; i < row_size; i++) 
        padded_row[i] = add_padding(row[i]);

    padded_row[row_size] = NULL;

    return padded_row;
}

void free_row(row_t row) {
    if (!row) return;

    row_t row_ptr = row;
    while (*row_ptr != NULL) {
        free(*row_ptr);
        row_ptr++;
    }

    free(row);
}
