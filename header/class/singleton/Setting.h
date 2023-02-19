#pragma once

class Setting
{
private:
	Setting();
	Setting(const Setting&) {}
	Setting& operator=(const Setting&) {}
	~Setting() {}
public:
	static Setting& singleton()
	{
		static Setting value;
		return value;
	}



	bool isDepth, isMSAA, isOutline;
	int shading;
};
