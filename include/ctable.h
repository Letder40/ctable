#ifndef CTABLE_H
#define CTABLE_H

#include <locale.h>
#include <stdint.h>

#include "lines.h"
#include "rows.h"

typedef char** row_t;

typedef struct {
    size_t size;
    size_t capacity;
    row_t* rows;
} Table;

Table create_table(const row_t* table, size_t rows_n);
#define TABLE(...) create_table((row_t[]){ __VA_ARGS__ }, sizeof(row_t[]){ __VA_ARGS__ } / sizeof(row_t))

typedef struct {
    Line top;
    Line middle;
    Line bottom;
    Table table;
    uint32_t* cols_size;
} TableBuilder;

TableBuilder table_build(Table table);

void table_push(Table* table, const row_t row);

void print_table(TableBuilder builder);

#endif
