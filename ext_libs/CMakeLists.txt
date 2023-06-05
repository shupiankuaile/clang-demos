cmake_minimum_required(VERSION 3.16)
project(external)

add_library(external empty.cpp)

add_subdirectory(dpi)
add_subdirectory(cJSON)

target_link_libraries(external
    ext_dmdpi
    ext_cjson
        )

# put "external" into External folder, too
set_target_properties(external
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        FOLDER "External"
        )


