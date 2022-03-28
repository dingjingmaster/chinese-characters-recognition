project(demo)

add_custom_target(gb2312 ALL ${CMAKE_C_COMPILER} -finput-charset=utf8 -fexec-charset=gb2312
        -o "${CMAKE_BINARY_DIR}/gb2312.run" "${CMAKE_SOURCE_DIR}/demo/gb2312.c")


