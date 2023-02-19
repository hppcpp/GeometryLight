#pragma once

#include "class/Transformation.h"

class Camera :public Transformation
{
public:
	Camera() {}
	explicit Camera(const glm::vec3&, const glm::vec3&);
	virtual ~Camera() {}

	void look()const;
	void look_topDown(const Transformation&)const;
	void look_tripod(const Transformation&)const;
	void rotate();
	void rotate_topDown(glm::vec3&);
	void rotate_tripod(glm::vec3&);
};
