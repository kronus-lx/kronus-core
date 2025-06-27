add_executable(object_examples "object_examples.cpp")

target_compile_definitions(object_examples PRIVATE OBJECT_EXAMPLES)
target_include_directories(object_examples PRIVATE ${PROJECT_SOURCE_DIR}/utils)

target_compile_features(fsystem_examples PRIVATE cxx_std_20)

install(TARGETS fsystem_examples 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)