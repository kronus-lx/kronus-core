add_executable(cclass_examples "person_init.c")

target_compile_definitions(cclass_examples PRIVATE FSYSTEM_EXAMPLES)
target_include_directories(cclass_examples PRIVATE ${PROJECT_SOURCE_DIR}/cclass)

target_compile_features(cclass_examples PRIVATE c_std_99)

install(TARGETS cclass_examples 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)