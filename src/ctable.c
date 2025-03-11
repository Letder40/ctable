#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdint.h>

#include "../include/ctable.h"

uint32_t* get_cols_size(row_t* rows) {
    uint32_t* cols_size = malloc(sizeof(uint32_t) * 5);
    size_t cols_size_capacity = 5;
    size_t cols_max_idx = 0;

    row_t* row_ptr = rows;
    
    while (*row_ptr != NULL) {
        row_t col_ptr = *row_ptr;
        uint32_t cols_idx = 0;
        while (*col_ptr != NULL) {
            uint32_t col_size = 0;
            char* char_ptr = *col_ptr;

            while (*char_ptr != '\0') {
                col_size++;      
                char_ptr++;
            }

            if (col_size > cols_size[cols_idx])
                cols_size[cols_idx] = col_size;
            
            cols_idx++;
            if (cols_idx > cols_max_idx)
                cols_max_idx = cols_idx;

            if (cols_idx >= cols_size_capacity) {
                cols_size_capacity *= 2;
                cols_size = realloc(cols_size, cols_size_capacity * sizeof(uint32_t));
                if (!cols_size) exit(EXIT_FAILURE);
            }
            col_ptr++;
        }
        row_ptr++;
    }

    cols_size[cols_max_idx] = 0; 
    return cols_size;
}

TableBuilder table_build(row_t* rows) {
    TableBuilder table_builder;
    table_builder.data = rows;

    row_t* rows_ptr = rows;
    row_t largest_row = *rows_ptr;
    rows_ptr++;

    table_builder.cols_size = get_cols_size(table_builder.data);

    table_builder.top = build_outer_line(table_builder.cols_size, TOP);
    table_builder.middle = build_inner_line(table_builder.cols_size);
    table_builder.bottom = build_outer_line(table_builder.cols_size, BOTTOM);

    return table_builder;
}

void table_builder_free(TableBuilder* table_builder) {
    line_free(&table_builder->top);
    line_free(&table_builder->middle);
    line_free(&table_builder->bottom);
    free(table_builder->cols_size);
}

#define print_line(line) wprintf(L"%ls\n", line);
#define print_data_line(line) wprintf(L"%ls\n", line); free(line);

void print_table(TableBuilder builder) {
    setlocale(LC_ALL, "");
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    row_t* row_ptr = builder.data;

    print_line(builder.top.data);

    while (*row_ptr != NULL) {
        print_data_line(build_data_line(*row_ptr, builder.cols_size).data);
        if (*++row_ptr != NULL) print_line(builder.middle.data);
    }

    print_line(builder.bottom.data);
    table_builder_free(&builder);
}
