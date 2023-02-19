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
struct Reflection
{
	vec3 diffuse;
	vec3 specular;
};

struct DirLight
{
	vec3 direction;

	Reflection reflection;
};
struct PointLight
{
	float compensation;
	vec3 attenuation;
	vec3 position;
	
	Reflection reflection;
};
struct SpotLight
{
	float compensation;
	vec2 cutoff;
	vec3 attenuation;
	vec3 direction;
	vec3 position;

	Reflection reflection;
};

uniform bool isMaterial;
uniform vec3 ambient;
uniform vec3 cameraPos;
uniform vec4 color;

uniform DirLight dirLight;
uniform Material material;
uniform PointLight pointLight;
uniform SpotLight spotLight;



vec3 dirLightFunc(DirLight light,vec3 cameraVec,vec3 norm);
vec3 ifMaterial(vec3 reflected,sampler2D texture2D);
vec3 pointLightFunc(PointLight light,vec3 pos,vec3 cameraVec,vec3 norm);
vec3 spotLightFunc(SpotLight light,vec3 pos,vec3 cameraVec,vec3 norm);

void main()
{
	vec3 norm=normalize(normal_fg);
	vec3 cameraVec=normalize(cameraPos-position_fg);
	
	vec3 resultColor=ifMaterial(ambient,material.diffuse);
	resultColor+=dirLightFunc(dirLight,cameraVec,norm);
	resultColor+=pointLightFunc(pointLight,position_fg,cameraVec,norm);
	resultColor+=spotLightFunc(spotLight,position_fg,cameraVec,norm);
	FragColor=vec4(resultColor,1.0f);
}

vec3 dirLightFunc(DirLight light,vec3 cameraVec,vec3 norm)
{
	vec3 lightVec=normalize(-light.direction);
	float diff=max(dot(norm,lightVec),0.0f);
	vec3 reflectVec=reflect(-lightVec,norm);
	float spec=pow(max(dot(cameraVec,reflectVec),0.0f),material.shininess);

	vec3 diffuse=light.reflection.diffuse*diff;
	diffuse=ifMaterial(diffuse,material.diffuse);
	vec3 specular=light.reflection.specular*spec;
	specular=ifMaterial(specular,material.specular);
	return diffuse+specular;
}
vec3 ifMaterial(vec3 reflected,sampler2D texture2D)
{
	if(isMaterial){return reflected*vec3(texture(texture2D,texCoord_fg));}
	else{return reflected*vec3(color);}
}
vec3 pointLightFunc(PointLight light,vec3 pos,vec3 cameraVec,vec3 norm)
{
	vec3 lightVec=normalize(light.position-pos);
	float diff=max(dot(norm,lightVec),0.0f);
	vec3 reflectVec=reflect(-lightVec,norm);
	float spec=pow(max(dot(cameraVec,reflectVec),0.0f),material.shininess);

	float distance=length(light.position-pos);
	float attenuation=light.compensation/(light.attenuation[0]+light.attenuation[1]*distance+light.attenuation[2]*pow(distance,2));

	vec3 diffuse=light.reflection.diffuse*diff*attenuation;
	diffuse=ifMaterial(diffuse,material.diffuse);
	vec3 specular=light.reflection.specular*spec*attenuation;
	specular=ifMaterial(specular,material.specular);
	return diffuse+specular;
}
vec3 spotLightFunc(SpotLight light,vec3 pos,vec3 cameraVec,vec3 norm)
{
	vec3 lightVec=normalize(light.position-pos);
	float diff=max(dot(norm,lightVec),0.0f);
	vec3 reflectVec=reflect(-lightVec,norm);
	float spec=pow(max(dot(cameraVec,reflectVec),0.0f),material.shininess);

	float distance=length(light.position-pos);
	float attenuation=light.compensation/(light.attenuation[0]+light.attenuation[1]*distance+light.attenuation[2]*pow(distance,2));

	float theta=dot(-lightVec,normalize(light.direction));
	float epsilon=light.cutoff[0]-light.cutoff[1];
	float intensity=clamp((theta-light.cutoff[1])/epsilon,0.0f,1.0f);

	vec3 diffuse=light.reflection.diffuse*diff*attenuation*intensity;
	diffuse=ifMaterial(diffuse,material.diffuse);
	vec3 specular=light.reflection.specular*spec*attenuation*intensity;
	specular=ifMaterial(specular,material.specular);

	return diffuse+specular;
}
