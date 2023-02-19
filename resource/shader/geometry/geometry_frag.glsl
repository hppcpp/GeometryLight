#version 400 core

in vec3 position_fg;
in vec3 normal_fg;
in vec2 texCoord_fg;

out vec4 FragColor;

struct Material
{
	float shininess;
	sampler2D diffuse;
	sampler2D specular;
};

uniform bool isTexture;
uniform Material material;
uniform vec4 color;

void main()
{
	vec3 resultColor;
	if(isTexture){resultColor=vec3(texture(material.diffuse,texCoord_fg));}
	else{resultColor=vec3(color);}
	FragColor=vec4(resultColor,1.0f);
}
