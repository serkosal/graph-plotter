#version 330 core

in vec4 graph_coord;

void main(void) {
	gl_FragColor = vec4(0.0, graph_coord.xy / 2.0 + vec2(0.5, 0.5), 1.0);
	//gl_FragColor = vec4(1.0);
}