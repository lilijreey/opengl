#version 330

 in vec3 vertex_position;
 in vec3 vertex_normal;
 in vec2 texture_coord;

uniform mat4 view, proj;

out vec3 normal;
out vec2 st;

void main() {
	st = texture_coord;
	normal = vertex_normal;
	gl_Position = proj * view * vec4 (vertex_position, 1.0);
}
