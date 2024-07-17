cmake_minimum_required(VERSION 3.20)

project(GraphPlotter_example)

set(SRCS "src/main.cpp" "src/utils.cpp")

add_executable(${PROJECT_NAME} ${SRCS})

add_subdirectory("graph-plotter")

target_include_directories(${PROJECT_NAME} 
	PUBLIC "graph-plotter/include"
	PUBLIC "graph-plotter/external/glad/include"
	PUBLIC "glfw/include"
	PUBLIC "graph-plotter/external/glm/glm"
)

target_link_directories(${PROJECT_NAME}
	PRIVATE "glfw/src"
	PRIVATE "graph-plotter/src/graph.cpp"
)

target_link_libraries(${PROJECT_NAME} GraphPlotter glfw)