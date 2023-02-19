#version 400 core

layout (location=0) in vec2 position_vt;
layout (location=1) in vec2 texCoord_vt;

out vec2 texCoord_fg;

void main()
{
	texCoord_fg=texCoord_vt;
	gl_Position=vec4(position_vt.x,position_vt.y,0.0f,1.0f);
}
