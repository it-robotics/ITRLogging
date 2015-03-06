add_executable(testcpp testcpp/main.cpp)
target_link_libraries(testcpp ${EXTRA_LIBS})

add_executable(testc testc/main.c)
target_link_libraries(testc ${EXTRA_LIBS})