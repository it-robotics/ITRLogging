cmake_minimum_required (VERSION 2.8)

project (ITRLogging)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DITRDEBUG")

add_subdirectory(src)
set(EXTRA_LIBS itr ${EXTRA_LIBS})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(test)

add_custom_target(copy-misc
    SOURCES ${CMAKE_SOURCE_DIR}/resources/itr-logging.conf
    COMMAND cp -u \"${CMAKE_SOURCE_DIR}/resources/itr-logging.conf\" \"${EXECUTABLE_OUTPUT_PATH}\"
)

add_dependencies(itr copy-misc)