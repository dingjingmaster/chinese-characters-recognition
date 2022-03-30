project(demo)

set(CMAKE_C_COMPILER gcc)

add_executable(demo-gb2312 "${CMAKE_SOURCE_DIR}/demo/demo-gb2312.c")
target_compile_options(demo-gb2312 PUBLIC -O0 -finput-charset=utf8 -fexec-charset=gb2312)
set_target_properties (demo-gb2312 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties (demo-gb2312 PROPERTIES OUTPUT_NAME "demo-gb2312.run")

add_executable(demo-utf8 "${CMAKE_SOURCE_DIR}/demo/demo-utf8.c")
target_compile_options(demo-utf8 PUBLIC -O0 -finput-charset=utf8 -fexec-charset=utf8)
set_target_properties (demo-utf8 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties (demo-utf8 PROPERTIES OUTPUT_NAME "demo-utf8.run")

add_executable(demo-int-char "${CMAKE_SOURCE_DIR}/demo/demo-int-char.c")
set_target_properties (demo-int-char PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties (demo-int-char PROPERTIES OUTPUT_NAME "demo-int-char.run")