#pragma once
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <glad/glad.h>
#include <glm.hpp>

void calculate(
	float (*func)(float, float),
	GLuint vao,
	GLuint vbo,
	GLuint ebo,
	GLuint& ind,
	const glm::ivec2 lines_num,
	glm::vec2 top_left,
	glm::vec2 bottom_right
);

#endif