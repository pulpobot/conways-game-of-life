cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

project(conways_game_of_life)
message("Compiling: ${PROJECT_NAME}")

#main src directory
set(SOURCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

#add third party source code
add_subdirectory(src/vendor/imgui)

#list of source files to use
message("Souce files: ${SOURCE}")

add_executable(${PROJECT_NAME} ${SOURCE})

#add third party libraries
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    add_compile_definitions(APPLE=true)
endif()