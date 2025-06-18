add_library(media INTERFACE)
add_library(futils INTERFACE)
add_library(sysfiles INTERFACE)

# COMPILE DEFINITIONS
target_compile_definitions(media INTERFACE
	MEDIA_EXPORTS
)
target_compile_definitions(futils INTERFACE
	FUTILS_EXPORTS
)
target_compile_definitions(sysfiles INTERFACE
	SYSFILES_EXPORTS
)

# INCLUDE CORRECT DIRECTORY PATHS
target_include_directories(media INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(futils INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(sysfiles INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)

# TARGET SOURCES
target_sources(futils INTERFACE
	FILE_SET HEADERS
	BASE_DIRS ${PROJECT_SOURCE_DIR}/fsystem/futils
	FILES "futils/futils.hpp"
)
target_sources(media INTERFACE
	FILE_SET HEADERS
	BASE_DIRS ${PROJECT_SOURCE_DIR}/fsystem/media
	FILES "media/raster_image.hpp"
)
target_sources(sysfiles INTERFACE
	FILE_SET HEADERS
	BASE_DIRS ${PROJECT_SOURCE_DIR}/fsystem/storage
	FILES "storage/system_files.hpp"
)

# INSTALL TARGETS
install(TARGETS media FILE_SET HEADERS)
install(TARGETS futils FILE_SET HEADERS)
install(TARGETS sysfiles FILE_SET HEADERS)