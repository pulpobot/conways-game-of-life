message("Adding Vendor: ${CMAKE_CURRENT_SOURCE_DIR}")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} VENDOR_SOURCES)

set(SOURCE ${SOURCE} ${VENDOR_SOURCES} PARENT_SCOPE)

message("Vendor src: ${VENDOR_SOURCES}")