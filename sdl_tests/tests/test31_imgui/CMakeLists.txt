Project(test_cimgui_opengl)
cmake_minimum_required(VERSION 3.0)
if(WIN32) # to make mingw work as all the others
set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif(WIN32)

include_directories(cimgui)

find_package(SDL2)
find_package(OpenGL)

include_directories(${OPENGL_INCLUDE_DIRS})


link_directories(cimgui)


add_executable(test_cimgui_opengl test_main_opengl.c)

target_compile_definitions(test_cimgui_opengl PUBLIC -DCIMGUI_USE_SDL -DCIMGUI_USE_OPENGL3)

target_link_libraries(test_cimgui_opengl cimgui_sdl SDL2 ${OPENGL_LIBRARIES})

