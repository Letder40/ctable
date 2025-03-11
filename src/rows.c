#include "../include/rows.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char* add_padding(const char* str) {
    size_t len = strlen(str);
    size_t padding_len = strlen(PADDING);
    size_t total_size = 
        len + (2 * padding_len) + 1;

    char* padded_str = (char*)malloc(total_size);
    if (!padded_str) {
        exit(EXIT_FAILURE);
    }

    strcpy(padded_str, PADDING);
    strcat(padded_str, str);
    strcat(padded_str, PADDING);

    return padded_str;
}

char** create_row(const char* row[]) {
    size_t count = 0;
    while (row[count] != NULL) count++;

    char** padded_row = (char**)malloc((count + 1) * sizeof(char*));
    if (!padded_row) {
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < count; i++) {
        padded_row[i] = add_padding(row[i]);
    }
    padded_row[count] = NULL;

    return padded_row;
}
