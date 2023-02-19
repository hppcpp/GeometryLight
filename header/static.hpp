#pragma once

#include <map>

#include "CAP/GLT.hpp"

#include "class/BulletTrajectory.h"
#include "class/Constv.h"
#include "class/Cuboid.h"
#include "class/Player.h"
#include "class/ShaderProgram.h"

inline const float* vec3dZero() { return CAP::vecZeroPtr<3, float>(); }
inline Constv& constv()
{
	static Constv value;
	return value;
}
inline std::map<int, ShaderProgram>& shaderProgramMap()
{
	static std::map<int, ShaderProgram> value;
	return value;
}
inline Player& player()
{
	static Player value(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f),
		10, 5,
		1,
		Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f)));
	return value;
}
