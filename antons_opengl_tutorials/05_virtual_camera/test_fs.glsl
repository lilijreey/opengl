#version 330 core

/*in vec3 colour;*/
/*out vec4 frag_colour;*/

in vec2 uv;
out vec3 color;

uniform sampler2D tex;

void main() {
	/*frag_colour = vec4 (colour, 1.0);*/
	color = texture(tex, uv).rgb;
}
