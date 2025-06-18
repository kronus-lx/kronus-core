# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Status Messages
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CXX compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C compiler flags: ${CMAKE_C_FLAGS}")
message(STATUS "CXX compiler flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_CXX_STANDARD_REQUIRED: ${CMAKE_CXX_STANDARD_REQUIRED}")
message(STATUS "CMAKE_CXX_EXTENSIONS: ${CMAKE_CXX_EXTENSIONS}")
message(STATUS "CMAKE_C_STANDARD: ${CMAKE_C_STANDARD}")
message(STATUS "CMAKE_C_STANDARD_REQUIRED: ${CMAKE_C_STANDARD_REQUIRED}")
message(STATUS "CMAKE_C_EXTENSIONS: ${CMAKE_C_EXTENSIONS}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

# Platform-specific settings
if(WIN32 OR WIN64)
    message(STATUS "Configuring for Windows")
    add_definitions(-DPLATFORM_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
elseif(UNIX)
    message(STATUS "Configuring for Linux")
    add_definitions(-DPLATFORM_LINUX)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Create library and executable
add_library(ccstring SHARED "ccstring.c" "ccstring.h")

# Include directories and compile features
target_include_directories(ccstring PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Set C standard for the library and examples
target_compile_features(ccstring PRIVATE c_std_99)

# Set the output name for the library and executable
target_compile_definitions(ccstring PRIVATE CCSTRING_EXPORTS)

# Install rules
install(TARGETS ccstring
    RUNTIME DESTINATION ccstring/bin
    LIBRARY DESTINATION ccstring/lib
    ARCHIVE DESTINATION ccstring/lib
)