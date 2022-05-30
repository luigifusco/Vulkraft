add_library(glm INTERFACE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_subdirectory(glfw)

#glm is a header only libs so we only need the include path
target_include_directories(glm INTERFACE glm)



 