#version 400 core

in vec2 texCoord_fg;

out vec4 FragColor;

uniform sampler2D frameTexture;

void main()
{
	FragColor=texture(frameTexture,texCoord_fg);
}
