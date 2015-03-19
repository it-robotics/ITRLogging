# cpp logging
add_executable(testcpp testcpp/main.cpp)
target_link_libraries(testcpp ${EXTRA_LIBS})

# c logging
add_executable(testc testc/main.c)
target_link_libraries(testc ${EXTRA_LIBS})

# c logging on cpp compiler
add_executable(testc_cpp testc/main.c)
set_target_properties(testc_cpp PROPERTIES LANGUAGE CXX)
target_link_libraries(testc_cpp ${EXTRA_LIBS})

# cpp logging disabled
add_executable(testcpp_off testcpp/main.cpp)
set_target_properties(testcpp_off PROPERTIES COMPILE_FLAGS -DITR_LOG_DISABLED)
target_link_libraries(testcpp_off ${EXTRA_LIBS})

# c logging disabled
add_executable(testc_off testc/main.c)
set_target_properties(testc_off PROPERTIES COMPILE_FLAGS -DITR_LOG_DISABLED)
target_link_libraries(testc_off ${EXTRA_LIBS})

# c logging on cpp compiler, disabled
add_executable(testc_cpp_off testc/main.c)
set_target_properties(testc_cpp_off PROPERTIES LANGUAGE CXX)
set_target_properties(testc_cpp_off PROPERTIES COMPILE_FLAGS -DITR_LOG_DISABLED)
target_link_libraries(testc_cpp_off ${EXTRA_LIBS})