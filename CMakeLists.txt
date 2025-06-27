cmake_minimum_required(VERSION 3.10)

project(kronus-core LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# For MSVC
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Enable Testing --> This is required for gtest testing
enable_testing()

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cclass)
add_subdirectory(ccstring)
add_subdirectory(fsystem)
add_subdirectory(utils)
add_subdirectory(math)
add_subdirectory(examples)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/*.hpp ${PROJECT_SOURCE_DIR}/*.ixx)
install(FILES ${HEADERS} DESTINATION include)