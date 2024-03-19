cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter  VERSION ${PROJECT_VESRION})

add_executable(ip_filter ip_filter.cpp ip_adr_pool.cpp)

set_target_properties(ip_filter PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

set(MASTER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")

install(TARGETS ip_filter RUNTIME DESTINATION bin)


if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)

else()
    # lots of warnings and all warnings as errors
    target_compile_options(ip_filter PRIVATE -Wall -Wextra -pedantic -Werror -g)
endif()

add_subdirectory(gtests)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
