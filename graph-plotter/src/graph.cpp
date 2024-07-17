#include "../include/graph.hpp"

#include <gtc/matrix_transform.hpp>

#include <vector>

void calculate(
	float (*func)(float, float),
	GLuint vao,
	GLuint vbo,
	GLuint ebo,
	GLuint& ind,
	const glm::ivec2 lines_num,
	glm::vec2 top_left,
	glm::vec2 bottom_right
)
{
	float w = (bottom_right.x - top_left.x) / lines_num.x;
	float h = (top_left.y - bottom_right.y) / lines_num.y;

	std::vector<glm::vec3> points;
	points.reserve((long long)lines_num.x * lines_num.y);
	for (int i = 0; i < lines_num.y; ++i)
		for (int j = 0; j < lines_num.x; ++j)
		{
			float x = (j * w) + top_left.x;
			float y = (i * h) + bottom_right.y;

			float z = func(x, y);

			points.push_back(glm::vec3{ 1 - 2 * (float)j / lines_num.x, 1 - 2 * (float)i / lines_num.y, z });
		}

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);

	std::vector<GLuint> indices;
	indices.reserve(2 * (lines_num.y * (lines_num.x - 1) + (lines_num.y - 1) * lines_num.x));

	for (int i = 0; i < lines_num.y; ++i)
	{
		for (int j = 0; j < lines_num.x - 1; ++j)
		{
			indices.push_back(i * lines_num.x + j);
			indices.push_back(i * lines_num.y + j + 1);
		}
	}

	for (int i = 0; i < lines_num.y - 1; ++i)
	{
		for (int j = 0; j < lines_num.x; ++j)
		{
			indices.push_back(i * lines_num.x + j);
			indices.push_back((i + 1) * lines_num.x + j);
		}
	}

	ind = indices.size();


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);
}
