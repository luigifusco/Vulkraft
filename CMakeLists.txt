cmake_minimum_required (VERSION 3.1)

project ("CG_Project")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Vulkan REQUIRED)

add_subdirectory(headers)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(main main.cpp)

add_custom_command(TARGET main PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders $<TARGET_FILE_DIR:main>/shaders)

make_directory(${CMAKE_CURRENT_BINARY_DIR}/bin/shaders)

target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(main glm glfw)

target_link_libraries(main Vulkan::Vulkan)