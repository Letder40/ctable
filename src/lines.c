#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "../include/lines.h"

Line new_line() {
    Line line = {
        .capacity = 0,
        .size = 0,
        .unicode_text = NULL,
    };
    return line;
}

void line_push(Line* line, wchar_t new_char) {
    if (line->size == line->capacity) {
        line->capacity = line->capacity ? line->capacity * 2 : 4;

        wchar_t* new_data =
            realloc(line->unicode_text, line->capacity * sizeof(wchar_t));

        if (!new_data) {
            free(line->unicode_text);
            exit(1);
        }

        line->unicode_text = new_data;
    }

    line->unicode_text[line->size++] = new_char;
}

void line_free(Line* line) {
    free(line->unicode_text);
    line->capacity = 0;
    line->size = 0;
}

Line build_outer_line(uint32_t* cols_size, Position position) {
    wchar_t left_corner;
    wchar_t right_corner;
    wchar_t intersection;

    switch (position) {
        case TOP:
            left_corner = TOP_LEFT_CORNER;
            right_corner = TOP_RIGHT_CORNER;
            intersection = TOP_INTERSECTION;
            break;
        case BOTTOM:
            left_corner = BOTTOM_LEFT_CORNER;
            right_corner = BOTTOM_RIGHT_CORNER;
            intersection = BOTTOM_INTERSECTION;
            break;
    }

    Line line = new_line();
    line_push(&line, left_corner);

    uint32_t* cols_size_ptr = cols_size;
    while (*cols_size_ptr != 0) {
        for (int i = 0; i < *cols_size_ptr; i++) line_push(&line, HORIZONTAL_LINE);
        cols_size_ptr++;
        if (*cols_size_ptr != 0) line_push(&line, intersection);
    }

    line_push(&line, right_corner);
    line_push(&line, L'\0');
    return line;
}

Line build_inner_line(uint32_t* cols_size) {
    Line line = new_line();
    line_push(&line, LEFT_INTERSECTION);

    uint32_t* cols_size_ptr = cols_size;
    while (*cols_size_ptr != 0) {
        for (int i = 0; i < *cols_size_ptr; i++) line_push(&line, HORIZONTAL_LINE);
        cols_size_ptr++;
        if (*cols_size_ptr != 0) line_push(&line, MIDDLE_INTERSECTION);
    }

    line_push(&line, RIGHT_INTERSECTION);
    line_push(&line, L'\0');
    return line;
}

Line build_data_line(row_t data, uint32_t* cols_size) {
    Line line = new_line();
    line_push(&line, VERTICAL_LINE);

    row_t data_ptr = data;
    uint32_t* cols_size_ptr = cols_size;

    while (*cols_size_ptr != 0) {
        char* char_ptr = (*data_ptr != NULL) ? *data_ptr : "";

        for (int i = 0; i < *cols_size_ptr; i++) {
            if (*char_ptr != '\0') {
                line_push(&line, *char_ptr++);
            } else {
                line_push(&line, ' ');
            }
        }
        data_ptr++;
        line_push(&line, VERTICAL_LINE);
        cols_size_ptr++;
    }

    line_push(&line, L'\0');
    return line;
}
