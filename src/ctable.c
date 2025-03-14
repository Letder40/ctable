#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/ctable.h"
#include "../include/rows.h"

void table_growth(Table* table) {
    table->capacity = table->capacity * 2;
    table->rows = realloc(table->rows, table->capacity * sizeof(row_t));
    if (!table->rows) exit(EXIT_FAILURE);
}

void table_push(Table* table, const row_t row) {
    if (table->size >= table->capacity) {
        table_growth(table);
    }

    table->rows[table->size++] = create_row(row);
}

Table create_table(const row_t* rows, size_t rows_n) {
    Table table;
    table.size = 0;
    table.capacity = 5;
    
    table.rows = malloc(sizeof(row_t) * 5);

    for (int i = 0; i < rows_n; i++)
        table_push(&table, rows[i]);

    return table;
}

void table_free(Table* table) {
    for (size_t i = 0; i < table->size; i++)
        free_row(table->rows[i]);

    table->size = 0;
    table->capacity = 0;
}

uint32_t* get_cols_size(Table table) {

    size_t cols_capacity = 5;
    uint32_t* cols_size = calloc(cols_capacity, sizeof(uint32_t));
    if (!cols_size) exit(EXIT_FAILURE);
    
    size_t max_cols = 0;

    for (size_t i = 0; i < table.size; i++) {
        row_t row = table.rows[i];
        size_t col_index = 0;

        while (*row != NULL) {

            uint32_t len = 0;
            char* col_str = *row;
            while (col_str[len] != '\0') {
                len++;
            }

            if (col_index >= cols_capacity) {
                cols_capacity *= 2;
                cols_size = realloc(cols_size, cols_capacity * sizeof(uint32_t));
                if (!cols_size) exit(EXIT_FAILURE);
            }

            if (len > cols_size[col_index]) {
                cols_size[col_index] = len;
            }

            col_index++;
            row++;
        }

        // Track the maximum number of columns encountered across all rows.
        if (col_index > max_cols) {
            max_cols = col_index;
        }
    }

    if (max_cols >= cols_capacity) {
        cols_capacity = max_cols + 1;
        cols_size = realloc(cols_size, cols_capacity * sizeof(uint32_t));
        if (!cols_size) exit(EXIT_FAILURE);
    }

    // sentinel value marking end of the array, a column never should be 0 so this is fine
    cols_size[max_cols] = 0;

    return cols_size;
}

TableBuilder table_build(Table table) {

    TableBuilder table_builder;

    table_builder.table = table;

    table_builder.cols_size = get_cols_size(table_builder.table);

    table_builder.top = build_outer_line(table_builder.cols_size, TOP);
    table_builder.middle = build_inner_line(table_builder.cols_size);
    table_builder.bottom = build_outer_line(table_builder.cols_size, BOTTOM);

    return table_builder;
}

void table_builder_free(TableBuilder* table_builder) {
    line_free(&table_builder->top);
    line_free(&table_builder->middle);
    line_free(&table_builder->bottom);
    table_free(&table_builder->table);
    free(table_builder->cols_size);
}

void print_table(TableBuilder builder) {
#ifdef _WIN32
    uint32_t locale = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
#else 
    char* locale = setlocale(LC_ALL, "");
#endif

    printf("%ls\n", builder.top.unicode_text);

    Table table = builder.table;

    for (int i; i<table.size; i++) {
        wchar_t* text_line = build_data_line(table.rows[i], builder.cols_size).unicode_text;
        printf("%ls\n", text_line);
        free(text_line);

        if (i + 1 < table.size)
            printf("%ls\n", builder.middle.unicode_text);
    }

    printf("%ls\n", builder.bottom.unicode_text);

#ifdef _WIN32
    SetConsoleOutputCP(locale);
#else
    setlocale(LC_ALL, locale);
#endif
    table_builder_free(&builder);
}
