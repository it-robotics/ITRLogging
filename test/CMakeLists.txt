# cpp logging
file(GLOB SOURCE_VAR "testcpp/*.cpp")
add_executable(testcpp ${SOURCE_VAR})
target_link_libraries(testcpp ${EXTRA_LIBS})

# c logging
file(GLOB SOURCE_VAR1 "testc/*.c")
add_executable(testc ${SOURCE_VAR1})
target_link_libraries(testc ${EXTRA_LIBS})

# c logging on cpp compiler
file(GLOB SOURCE_VAR "testc/*.c")
add_executable(testc_cpp ${SOURCE_VAR})
set_target_properties(testc_cpp PROPERTIES LANGUAGE CXX)
target_link_libraries(testc_cpp ${EXTRA_LIBS})

# cpp logging disabled
file(GLOB SOURCE_VAR "testcpp/*.cpp")
add_executable(testcpp_off ${SOURCE_VAR})
set_target_properties(testcpp_off PROPERTIES COMPILE_FLAGS -DITR_LOG_DISABLED)
target_link_libraries(testcpp_off ${EXTRA_LIBS})

# c logging disabled
file(GLOB SOURCE_VAR "testc/*.c")
add_executable(testc_off ${SOURCE_VAR})
set_target_properties(testc_off PROPERTIES COMPILE_FLAGS -DITR_LOG_DISABLED)
target_link_libraries(testc_off ${EXTRA_LIBS})

# c logging on cpp compiler, disabled
file(GLOB SOURCE_VAR "testc/*.c")
add_executable(testc_cpp_off ${SOURCE_VAR})
set_target_properties(testc_cpp_off PROPERTIES LANGUAGE CXX)
set_target_properties(testc_cpp_off PROPERTIES COMPILE_FLAGS -DITR_LOG_DISABLED)
target_link_libraries(testc_cpp_off ${EXTRA_LIBS})
