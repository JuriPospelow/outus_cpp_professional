cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld  VERSION ${PROJECT_VESRION})

configure_file(git_hub_version.h.in git_hub_version.h)

add_executable(hello main.cpp)
add_library(hello_lib lib.cpp)
set_target_properties(hello PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

set(MASTER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")
message(${MASTER_DIR})

install(TARGETS hello RUNTIME DESTINATION bin)

add_custom_target(
    increment_build_version
    COMMAND ${CMAKE_COMMAND}
        -P "${MASTER_DIR}increment_script.cmake"
)

add_dependencies(hello increment_build_version)

target_link_libraries(hello PRIVATE
    hello_lib
)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)

else()
    # lots of warnings and all warnings as errors
    target_compile_options(hello PRIVATE -Wall -Wextra -pedantic -Werror -g)
endif()

add_subdirectory(gtests)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
