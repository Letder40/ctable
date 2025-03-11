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
