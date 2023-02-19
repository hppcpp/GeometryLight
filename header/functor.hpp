#pragma once

#include "class/Geometry.h"

struct DisplayGeometry :public std::unary_function<const std::shared_ptr<Geometry>&, void>
{
	void operator()(const std::shared_ptr<Geometry>& geometryPtr)const
	{
		geometryPtr->draw();
	}
};

struct UpdateGeometry :public std::unary_function<std::shared_ptr<Geometry>&, void>
{
	void operator()(std::shared_ptr<Geometry>& geometryPtr)const
	{
		geometryPtr->update();
	}
};
