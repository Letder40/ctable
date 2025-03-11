#ifndef LINES_H
#define LINES_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    TOP_LEFT_CORNER = L'┌',
    TOP_RIGHT_CORNER = L'┐',
    BOTTOM_LEFT_CORNER = L'└',
    BOTTOM_RIGHT_CORNER = L'┘',
    TOP_INTERSECTION = L'┬',
    LEFT_INTERSECTION = L'├',
    MIDDLE_INTERSECTION = L'┼',
    RIGHT_INTERSECTION = L'┤',
    BOTTOM_INTERSECTION = L'┴',
    VERTICAL_LINE = L'│',
    HORIZONTAL_LINE = L'─'
} TableChars;

typedef enum {
    TOP,
    BOTTOM,
} Position;

typedef struct {
    wchar_t* data;
    size_t capacity;
    size_t size;
} Line;

typedef char** row_t;

Line new_line();
void line_push(Line* line, wchar_t new_char);
void line_free(Line* line);

Line build_outer_line(uint32_t* cols_size, Position position);
Line build_inner_line(uint32_t* cols_size);
Line build_data_line(row_t data, uint32_t* cols_size);

#endif
