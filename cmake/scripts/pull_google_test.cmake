function(pull_google_test project)
    
    enable_testing()

    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
    )

    # Make Google Test Available
    FetchContent_MakeAvailable(googletest)

    # Target the Directories
    target_include_directories(${project} PRIVATE "${gtest_SOURCE_DIR}/include")

    # Link the necessary GoogleTest libraries
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(${project} PRIVATE gtestd gtest_main)
    else()
        target_link_libraries(${project} PRIVATE gtest gtest_main)
    endif()

    file(GLOB_RECURSE HEADERS ${gtest_SOURCE_DIR}/include/*.h)
    file(GLOB_RECURSE BINS ${gtest_SOURCE_DIR}/*.dll)
    file(GLOB_RECURSE LIBS ${gtest_SOURCE_DIR}/*.lib)
    
    install(FILES ${HEADERS} DESTINATION include)
    install(FILES ${LIBS} DESTINATION lib)
    install(FILES ${BINS} DESTINATION bin)

    message(STATUS ">> INSTALLED GTEST FRAMEWORK")
    
endfunction()
