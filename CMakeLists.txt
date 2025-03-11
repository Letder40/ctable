CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(ctable)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_library(ctable STATIC
    src/ctable.c
    src/rows.c
    src/lines.c
)

add_executable(example example/example.c)
target_link_libraries(example ctable)
