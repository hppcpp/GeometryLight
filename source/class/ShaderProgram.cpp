#include "class/ShaderProgram.h"

const std::string ShaderProgram::suffix_glsl = ".glsl";
const std::string ShaderProgram::postfix_frag = "_frag";
const std::string ShaderProgram::postfix_vert = "_vert";
const std::string ShaderProgram::logFile = "ShaderProgram_log.txt";

ShaderProgram::ShaderProgram(const std::string& path) :
	fragment((path + ShaderProgram::postfix_frag + ShaderProgram::suffix_glsl).c_str(), GL_FRAGMENT_SHADER),
	vertex((path + ShaderProgram::postfix_vert + ShaderProgram::suffix_glsl).c_str(), GL_VERTEX_SHADER)
{
	program.create();
	program.attachShader(vertex);
	program.attachShader(fragment);
	program.link();
	statusLog(ShaderProgram::logFile.c_str());
}

void ShaderProgram::compile_link(const std::string& path, bool deleting = true)
{
	if (deleting) { deletion(); }

	vertex.create(GL_VERTEX_SHADER);
	vertex.compile((path + ShaderProgram::postfix_vert + ShaderProgram::suffix_glsl).c_str());
	fragment.create(GL_FRAGMENT_SHADER);
	fragment.compile((path + ShaderProgram::postfix_frag + ShaderProgram::suffix_glsl).c_str());

	program.create();
	program.attachShader(vertex);
	program.attachShader(fragment);
	program.link();
	statusLog(ShaderProgram::logFile.c_str());
}
void ShaderProgram::deletion()const
{
	vertex.deletion();
	fragment.deletion();

	program.detachShader(vertex);
	program.detachShader(fragment);
	program.deletion();
}
void ShaderProgram::statusLog(const char* const logPath)const
{
	vertex.compileStatus(true, logPath);
	fragment.compileStatus(true, logPath);
	program.linkStatus(true, logPath);
}
