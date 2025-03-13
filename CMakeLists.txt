CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(ctable)

include_directories(include)

add_executable(example example/example.c)

add_library(ctable_static STATIC
    src/ctable.c
    src/rows.c
    src/lines.c
)

add_library(ctable SHARED
    src/ctable.c
    src/rows.c
    src/lines.c
)

set_target_properties(ctable_static PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
)

set_target_properties(ctable PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
)

set_target_properties(example PROPERTIES
    EXECUTABLE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../example
)

target_link_libraries(example ctable)
