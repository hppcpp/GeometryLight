#include <stb-image/stb_image.h>

#include "class/singleton/Global.h"
#include "class/singleton/Setting.h"
#include "function/universal.h"
#include "static.hpp"

bool geometryIsOver(const std::shared_ptr<Geometry>& geometryPtr) { return geometryPtr->getIsOver(); }
unsigned int textureFile(const char* const filePath)
{
	if (!filePath) { return 0; }
	unsigned int textureID=0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int height=0, nrChannel=0, width=0;

	unsigned char* image = stbi_load(filePath, &width, &height, &nrChannel, 0);
	if (image)
	{
		GLenum format;
		if (nrChannel == 1) { format = GL_RED; }
		else if (nrChannel == 3) { format = GL_RGB; }//jpg
		else if (nrChannel == 4) { format = GL_RGBA; }//png

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { std::cout << "textureFile  " << filePath << std::endl; }

	stbi_image_free(image);
	return textureID;
}
unsigned int texturePath(const char* const file, const std::string& path)
{
	std::string filePath = std::string(file);
	filePath = path + '/' + file;
	return textureFile(filePath.c_str());
}
void displayScene()
{
}
void polarRight(const float* const polar,float* const right)
{
	right[0] = 1;
	right[1] = static_cast<int>(polar[1] + 270) % CAP::PERIGON;
}
void polar_rectangularRight(const float* const polar,float* const right)
{
	float polRt[2];
	polarRight(polar,polRt);
	CAP::polar_rectangular(polRt,right);
}
void spherical_rectangularRight(const float* const spherical,float* const right)
{
	float sphRt[3];
	sphericalRight(spherical,sphRt);
	CAP::spherical_rectangular(sphRt,right);
}
void spherical_rectangularUp(const float* const spherical,float* const up)
{
	float sphUp[3];
	sphericalUp(spherical,sphUp);
	CAP::spherical_rectangular(sphUp,up);
}
void sphericalRight(const float* const spherical,float* const right)
{
	right[0] = 1;
	right[1] = static_cast<int>(spherical[1] + 270) % CAP::PERIGON;
	right[2] = 90;
}
void sphericalUp(const float* const spherical,float* const up)
{
	up[0] = 1;
	up[1] = spherical[1];
	up[2] = static_cast<int>(spherical[2] + 270) % CAP::PERIGON;
}
