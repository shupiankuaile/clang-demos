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
        libs/utils.c
        libs/conf.c
        libs/log.c
        libs/map.c
        libs/vec.c
        libs/uuid4.c
        libs/sandbird.c
        libs/ini.c
        )
list(APPEND MYTOOLS_HEADER
        libs/utils.h
        libs/conf.h
        libs/log.h
        libs/map.h
        libs/vec.h
        libs/uuid4.h
        libs/sandbird.h
        libs/ini.h
        )
set(MYTOOLS_TEST_SOURCE )
set(MYTOOLS_TEST_HEADER )
list(APPEND MYTOOLS_TEST_SOURCE
        linux_tests/test_suite.c
        linux_tests/time_test.c
        linux_tests/dir_test.c
        linux_tests/proc_test.c
        linux_tests/thread_test.c
        )
list(APPEND MYTOOLS_TEST_HEADER
        linux_tests/test_suite.h
        linux_tests/time_test.h
        linux_tests/dir_test.h
        linux_tests/proc_test.h
        linux_tests/thread_test.h
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

