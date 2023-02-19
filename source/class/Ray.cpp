#include "class/Ray.h"

#include "CAP/GLT.hpp"

Ray::Ray(double range, int shad, const glm::vec3& pos, const glm::vec3& dir, const glm::vec4& col,
	const glm::vec3& posi, const glm::vec3& rota, const glm::vec3& sca) :
	Line(shad, col, pos, pos, posi, rota, sca)
{
	glm::vec3 vecTemp;
	CAP::spherical_rectangular_normalized(&dir[0], &vecTemp[0]);
	CAP::vectorAddAssign(3, range, &endpoint[1][0], &vecTemp[0]);
}
