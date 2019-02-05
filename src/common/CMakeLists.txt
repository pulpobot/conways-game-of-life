message("Adding common source: ${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE COMMON_SOURCE "*.cpp" "*.hpp" "*.h")
message("common src: ${COMMON_SOURCE}")
set(SOURCE ${SOURCE} ${COMMON_SOURCE} PARENT_SCOPE)