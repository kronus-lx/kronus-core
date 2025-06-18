add_executable(ccstring_examples "ccstring_examples.c")

target_link_libraries(ccstring_examples PRIVATE ccstring)
target_compile_definitions(ccstring_examples PRIVATE CCSTRING_EXAMPLES)
target_include_directories(ccstring_examples PRIVATE ${PROJECT_SOURCE_DIR}/ccstring)

target_compile_features(ccstring_examples PRIVATE c_std_99)

install(TARGETS ccstring_examples 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)