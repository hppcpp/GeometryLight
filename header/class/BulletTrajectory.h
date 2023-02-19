#pragma once

#include <windows.h>

#include "class/Ray.h"

class BulletTrajectory : public Ray
{
protected:
	const DWORD start;
public:
	static const double spell;



	BulletTrajectory(double, int, const glm::vec3&, const glm::vec3&, const glm::vec4&,
		const glm::vec3& posi = glm::vec3(0.0f), const glm::vec3& rota = glm::vec3(0.0f), const glm::vec3& sca = glm::vec3(1.0f));

	bool getIsOver()const;
	DWORD getStart()const { return start; }
};
