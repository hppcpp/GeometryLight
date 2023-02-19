#version 400 core

layout (location=0) in vec3 position_vt;

out vec3 position_fg;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	position_fg=vec3(model*vec4(position_vt,1.0f));
	gl_Position=projection*view*model*vec4(position_vt,1.0f);
}
