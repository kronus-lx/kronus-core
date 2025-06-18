add_executable(fsystem_examples "fsystem_examples.cpp")

target_compile_definitions(fsystem_examples PRIVATE FSYSTEM_EXAMPLES)
target_include_directories(fsystem_examples PRIVATE ${PROJECT_SOURCE_DIR}/fsystem)

target_compile_features(fsystem_examples PRIVATE cxx_std_20)

install(TARGETS fsystem_examples 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)