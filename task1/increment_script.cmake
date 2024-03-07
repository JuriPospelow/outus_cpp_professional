#basic definitions

set(HEADER_FILE "version.h")
set(CACHE_FILE "BuildNumberCache.txt")

#Reading data from file + incrementation
IF(EXISTS ${CACHE_FILE})
    file(READ ${CACHE_FILE} BUILD_VERSION)
    math(EXPR BUILD_VERSION "${BUILD_VERSION}+1")
ELSE()
    set(BUILD_VERSION "1")
ENDIF()

message("Build number: " ${BUILD_VERSION})

#Update the cache
file(WRITE ${CACHE_FILE} "${BUILD_VERSION}")

#Create the header
file(WRITE ${HEADER_FILE} "#ifndef INCREMENT_H\n#define INCREMENT_H\n\n#define BUILD_VERSION ${BUILD_VERSION}\n\n#endif")
