#include <stdio.h>
#include "../include/ctable.h"

int main(int argc, char** argv) {

    Table table = TABLE(
        ROW("Letder40's", "Ctable"),
        ROW("CTABLE"),
        ROW("CTABLE", "EASY TABLES"),
        ROW("CTABLE", "EASY TABLES", "FOR C LANGUAGE")
    );

    TableBuilder builder = table_build(table);

    printf("Ctable usage example:\n");

    //
    // All ctable's components will be freed after this call.
    // 
    
    print_table(builder);

    // 
    // It is possible to push more rows before calling table_build() 
    // So it is possible to create a table that will growth dynamically
    // until print_build is called.
    // 

    Table table2 = TABLE(ROW("COLUMN ID", "DATA"));

    for (int i = 0; i < 5; i++) {
        char column[9] = {0};
        snprintf(column, 9, "column %d", i + 1);

        row_t row = ROW(column, "DATA....");
        table_push(&table2, row);
    }

    builder = table_build(table2);
    printf("\nCtable's Dynamic table usage example:\n");
    print_table(builder);
}
