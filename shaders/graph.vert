#version 330 core

layout (location = 0) in vec3 coord3d;

uniform mat4 MVP;

out vec4 graph_coord;

void main(void) {
	graph_coord = MVP * vec4(coord3d, 1);

	gl_Position = graph_coord;
}