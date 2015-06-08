#version 330

in vec3 vertex_position;
in vec2 vertex_uv;

uniform mat4 mvp;

out vec2 uv;


void main() {
	uv = vertex_uv;
	gl_Position = mvp* vec4 (vertex_position, 1.0);
}
