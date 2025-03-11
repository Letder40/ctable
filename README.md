# Ctable

## Introduction
Ctable is a library that allows to generate printable tables easily
This was originally a module of (netcalc)[https://github.com/Letder40/netcalc], but I ended creating a library to use this in others c projects.

## How it works?
link the static library lib/libctable.a to your project.

```c
#include "../include/ctable.h"
int main(int argc, char** argv) {
    row_t* table = TABLE(
        ROW("Letder40's", "Ctable"),
        ROW("CTABLE"),
        ROW("CTABLE", "EASY TABLES"),
        ROW("CTABLE", "EASY TABLES", "FOR C LANGUAGE")
    );

    TableBuilder builder = table_build(table);
    // All table's components will be freed after this call
    print_table(builder);
}
```
### Take in count

Use the macro TABLE to define the table structure.
Use the macro ROW to define each row.
All memmory allocation will be freed when print_table is called.
# ctable
