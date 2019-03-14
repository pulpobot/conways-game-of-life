message("Adding common source: ${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE EVENTS_SOURCE "*.cpp" "*.hpp" "*.h")
message("common src: ${EVENTS_SOURCE}")
set(SOURCE ${SOURCE} ${EVENTS_SOURCE} PARENT_SCOPE)