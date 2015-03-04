file(GLOB_RECURSE SOURCE_VAR *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(itr SHARED ${SOURCE_VAR})

target_link_libraries(itr log4cxx)