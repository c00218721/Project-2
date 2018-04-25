#version 400

uniform sampler2D f_texture;

in vec4 color;
in vec2 uv;
out vec4 fColor;

void main() {
	fColor = texture2D(f_texture, uv);
}