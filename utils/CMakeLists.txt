add_library(object INTERFACE)
add_library(matrix INTERFACE)
add_library(streams INTERFACE)

target_compile_definitions(object INTERFACE
	OBJECT_EXPORTS
)
target_compile_definitions(matrix INTERFACE
	OBJECT_EXPORTS
)
target_compile_definitions(streams INTERFACE
	OBJECT_EXPORTS
)

target_include_directories(object INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(matrix INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(streams INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)

# TARGET SOURCES
target_sources(object INTERFACE
	FILE_SET HEADERS
	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
	FILES "Object.hpp"
)
# TARGET SOURCES
target_sources(matrix INTERFACE
	FILE_SET HEADERS
	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
	FILES "Matrix.hpp"
)
# TARGET SOURCES
target_sources(streams INTERFACE
	FILE_SET HEADERS
	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
	FILES "Streams.hpp"
)

install(TARGETS object FILE_SET HEADERS)
install(TARGETS matrix FILE_SET HEADERS)