#pragma once

#include <iostream>
#include <string>

#include "CAP/GLSL/shader.hpp"

class ShaderProgram
{
private:
	CAP::GLSL::Program program;
	CAP::GLSL::Shader fragment, vertex;

public:
	static const std::string logFile, postfix_frag, postfix_vert, suffix_glsl;



	ShaderProgram() :program(0) {  }
	ShaderProgram(const std::string&);

	void compile_link(const std::string&, bool);
	void deletion()const;
	void statusLog(const char* const)const;

	const CAP::GLSL::Program& getProgram()const { return program; }
	CAP::GLSL::Program& setProgram() { return program; }
	const CAP::GLSL::Shader& getFragment()const { return fragment; }
	const CAP::GLSL::Shader& getVertex()const { return vertex; }
	CAP::GLSL::Shader& setFragment() { return fragment; }
};
