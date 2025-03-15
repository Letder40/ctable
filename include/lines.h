#ifndef LINES_H
#define LINES_H

#include <stddef.h>
#include <stdint.h>

#include "../include/rows.h"

typedef struct {
    wchar_t* unicode_text;
    size_t capacity;
    size_t size;
} Line;

void line_free(Line* line);

typedef enum {
    TOP,
    BOTTOM,
} Position;

Line build_outer_line(uint32_t* cols_size, Position position);
Line build_inner_line(uint32_t* cols_size);
Line build_data_line(row_t data, uint32_t* cols_size);

#endif
