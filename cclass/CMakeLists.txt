add_library(cclass INTERFACE)
target_compile_definitions(cclass INTERFACE
	CCLASS_EXPORTS
)
target_sources(cclass INTERFACE
    FILE_SET HEADERS
    BASE_DIRS "${PROJECT_SOURCE_DIR}/cclass"
    FILES "cclass.h"
)