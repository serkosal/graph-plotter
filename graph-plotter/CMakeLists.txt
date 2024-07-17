cmake_minimum_required(VERSION 3.20)

project(GraphPlotter)

set(SRCS "src/graph.cpp" "external/glad/src/glad.c")

add_library(${PROJECT_NAME} STATIC ${SRCS})
#add_library(${PROJECT_NAME} SHARED ${SRCS})

add_subdirectory("external/glfw")

target_include_directories(${PROJECT_NAME} 
	PUBLIC "include/graph.hpp"
	PUBLIC "external/glad/include"
	PUBLIC "external/glfw/include"
	PUBLIC "external/glm/glm"
)

target_link_directories(${PROJECT_NAME}
	PRIVATE "external/glfw/src"
)

target_link_libraries(${PROJECT_NAME}
	glfw
)