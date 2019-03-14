message("Adding main source: ${CMAKE_CURRENT_SOURCE_DIR}")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} MAIN_SOURCE)
message("main src: ${MAIN_SOURCE}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/events)

set(SOURCE ${SOURCE} ${MAIN_SOURCE} PARENT_SCOPE)

