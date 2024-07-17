#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <graph.hpp>

#include "camera.hpp"
#include "utils.hpp"

const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

GLFWwindow* g_window = nullptr;

GLuint vao;
GLuint vbo;
GLuint ebo;

GLuint shader;
GLuint MVP;

void init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	g_window = glfwCreateWindow(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		"graph plotter",
		NULL,
		NULL
	);

	if (g_window == nullptr)
		throw std::runtime_error("Failed to create GLFW window!\n");

	glfwMakeContextCurrent((GLFWwindow*)g_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD");

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSetFramebufferSizeCallback((GLFWwindow*)g_window,
		[](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);

	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	shader = program_from_files("graph.vert", "graph.frag");

	MVP = glGetUniformLocation(shader, "MVP");
	//texture_transform = glGetUniformLocation(shader, "texture_transform");
	//uniform_texture = glGetUniformLocation(shader, "ourTexture");

	glClearColor(0.f, 0.f, 0.f, 1.f);
}
