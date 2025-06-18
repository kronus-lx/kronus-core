add_library(${PROJECT_NAME}_math SHARED "electrical.cpp" "electrical.hpp" "pythagoras.hpp" "pythagoras.cpp")

target_compile_features(${PROJECT_NAME}_math PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}_math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME}_math 
    RUNTIME DESTINATION ${PROJECT_NAME}_math/bin
    LIBRARY DESTINATION ${PROJECT_NAME}_math/lib
    ARCHIVE DESTINATION ${PROJECT_NAME}_math/lib
)