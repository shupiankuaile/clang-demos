cmake_minimum_required(VERSION 3.16)
project(my_tools C)

set(CMAKE_C_STANDARD 99)
set(PROJECT_NAME my_tools)

find_package(PkgConfig REQUIRED)
pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)

add_subdirectory(ext_libs)

set(MYTOOLS_SOURCE )
set(MYTOOLS_HEADER )
list(APPEND MYTOOLS_SOURCE
        src/main.c
        src/utils.c
        src/conf.c
        src/log.c
        src/map.c
        src/vec.c
        src/uuid4.c
        src/sandbird.c
        src/ini.c
        )
list(APPEND MYTOOLS_HEADER
        src/utils.h
        src/conf.h
        src/log.h
        src/map.h
        src/vec.h
        src/uuid4.h
        src/sandbird.h
        src/ini.h
        )
set(MYTOOLS_TEST_SOURCE )
set(MYTOOLS_TEST_HEADER )
list(APPEND MYTOOLS_TEST_SOURCE
        tests/test_suite.c
        tests/time_test.c
        tests/dir_test.c
        tests/proc_test.c
        tests/thread_test.c
        )
list(APPEND MYTOOLS_TEST_HEADER
        tests/test_suite.h
        tests/time_test.h
        tests/dir_test.h
        tests/proc_test.h
        tests/thread_test.h
        )
set(all_code_files
        ${MYTOOLS_HEADER}
        ${MYTOOLS_SOURCE}
        ${MYTOOLS_TEST_SOURCE}
        ${MYTOOLS_TEST_HEADER}
        )

add_executable(${PROJECT_NAME} ${all_code_files})

target_link_libraries(${PROJECT_NAME}
        ext_libs
        pthread
        )

if (X11_FOUND)
    include_directories(${X11_INCLUDE_DIRS})
    link_directories(${X11_LIBRARY_DIRS})
    target_link_libraries(${PROJECT_NAME}  PkgConfig::X11)
    message(STATUS "found library:${X11_LIBRARIES}")
endif ()

