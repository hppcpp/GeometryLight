#version 400 core

layout (location=0) in vec3 position_vt;
layout (location=1) in vec3 normal_vt;
layout (location=2) in vec2 texCoord_vt;

out vec3 position_fg;
out vec3 normal_fg;
out vec2 texCoord_fg;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	position_fg=vec3(model*vec4(position_vt,1.0f));
	normal_fg=mat3(transpose(inverse(model)))*normal_vt;
	texCoord_fg=texCoord_vt;
	gl_Position=projection*view*model*vec4(position_vt,1.0f);
}
