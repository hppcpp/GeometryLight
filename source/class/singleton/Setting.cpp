#include "class/singleton/Setting.h"
#include "enum/SHADING.h"

Setting::Setting() :
	isDepth(false),
	isMSAA(false),
	isOutline(false),
	shading(SOLID)
{}
