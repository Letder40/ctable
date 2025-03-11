#ifndef CTABLE_H
#define CTABLE_H

#include <locale.h>
#include <stdint.h>
#include "lines.h"
#include "rows.h"

typedef struct {
    Line top;
    Line middle;
    Line bottom;
    uint32_t* cols_size;
    row_t* data;
} TableBuilder;

TableBuilder table_build(row_t* rows);

void print_table(TableBuilder builder);

#define TABLE(...) \
    (char**[]) { __VA_ARGS__, NULL }


#endif
