#pragma once

class ImGuiSetting
{
private:
	ImGuiSetting();
	ImGuiSetting(const ImGuiSetting&) {}
	ImGuiSetting& operator=(const ImGuiSetting&) {}
	~ImGuiSetting() {}
public:
	static ImGuiSetting& singleton()
	{
		static ImGuiSetting value;
		return value;
	}
	

	
	float dragSpeed;
};
