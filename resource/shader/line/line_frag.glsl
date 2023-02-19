#version 400 core

in vec3 position_fg;

out vec4 FragColor;

uniform vec4 color;

void main()
{
	FragColor=color;
}
