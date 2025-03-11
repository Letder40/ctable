#ifndef ROWS_H
#define ROWS_H

#define PADDING "  "

char** create_row(const char* row[]);
#define ROW(...) create_row((const char*[]){ __VA_ARGS__, NULL })

#endif
