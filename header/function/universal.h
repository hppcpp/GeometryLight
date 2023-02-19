#pragma once

#include <string>

#include "class/BulletTrajectory.h"
#include "class/Cuboid.h"
#include "class/ShaderProgram.h"

bool geometryIsOver(const std::shared_ptr<Geometry>&);
unsigned int textureFile(const char* const);
unsigned int texturePath(const char* const, const std::string&);
void displayScene();
void polarRight(const float* const, float* const);
void polar_rectangularRight(const float* const, float* const);
void spherical_rectangularRight(const float* const, float* const);
void spherical_rectangularUp(const float* const, float* const);
void sphericalRight(const float* const, float* const);
void sphericalUp(const float* const, float* const);
