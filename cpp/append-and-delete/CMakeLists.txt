cmake_minimum_required(VERSION 3.9)

project(Play LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR} ${HOME}/opt/gsl/include)

add_executable(main main.cpp)

add_custom_target(run
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

if(NOT MSVC)
    target_compile_options(main
        PRIVATE
            -Wall               # "all" warnings
            -Wextra             # extra warnings
            -pedantic           # even more warnings
            -O                  # optimize
            -ftrapv)            # trap on integer overflow
endif()
