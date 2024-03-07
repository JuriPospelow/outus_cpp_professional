cmake_minimum_required(VERSION 3.5)

project(01.homework)

add_executable(hello main.cpp)
set_target_properties(hello PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)

else()
    # lots of warnings and all warnings as errors
    target_compile_options(hello PRIVATE -Wall -Wextra -pedantic -Werror -g)
endif()

# add_subdirectory(gtests)
