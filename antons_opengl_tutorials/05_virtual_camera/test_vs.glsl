#version 330

in vec3 vertex_position;
in vec3 vertex_colour;

uniform mat4 mvp;

out vec3 colour;

void main() {
	colour = vertex_colour;
	gl_Position = mvp* vec4 (vertex_position, 1.0);
}
