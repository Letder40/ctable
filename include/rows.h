#ifndef ROWS_H
#define ROWS_H

#define PADDING "  "

typedef char** row_t;

row_t create_row(const row_t row);

void free_row(row_t row);

#define ROW(...) (row_t)(char *[]){ __VA_ARGS__, NULL }

#endif
