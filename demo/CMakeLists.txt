project(demo)

add_custom_target(gb2312 ALL ${CMAKE_C_COMPILER} -O0 -finput-charset=utf8 -fexec-charset=gb2312
        -o "${CMAKE_BINARY_DIR}/demo-gb2312.run" "${CMAKE_SOURCE_DIR}/demo/demo-gb2312.c")

add_custom_target(utf8 ALL ${CMAKE_C_COMPILER} -O0 -finput-charset=utf8 -fexec-charset=utf8
        -o "${CMAKE_BINARY_DIR}/demo-utf8.run" "${CMAKE_SOURCE_DIR}/demo/demo-utf8.c")


