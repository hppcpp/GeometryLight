/**/
#include<GL/glew.h>

#include<vector>

#include"CAP/file.h"

#ifndef CAP_GLSL_shader_h
#define CAP_GLSL_shader_h
namespace CAP
{

namespace GLSL
{
class Program;
class Shader;

class Program
{
	private:
		GLuint programHandle;
	public:
		Program();
		explicit Program(GLuint);
		
		bool isZero()const{return programHandle==0;}
		int activeAttributes(bool print=false,const char* const path=0)const;
		int activeUniforms(bool print=false,const char* const path=0)const;
		int attachedShaders()const;
		int deleteStatus()const;
		int linkStatus(bool print=false,const char* const path=0)const;
		void attachShader(GLuint shaderHandle)const{glAttachShader(programHandle,shaderHandle);}
		void attachShader(const Shader&)const;
		void deletion()const{glDeleteProgram(programHandle);}
		void detachShader(GLuint shaderHandle)const{glDetachShader(programHandle,shaderHandle);}
		void detachShader(const Shader&)const;
		void link()const
		{if(programHandle!=0){glLinkProgram(programHandle);}}
		
		void setUniform1f(const char* const name,GLfloat value)const
		{glUniform1f(glGetUniformLocation(programHandle,name),value);}
		void setUniform1i(const char* const name,GLint value)const
		{glUniform1i(glGetUniformLocation(programHandle,name),value);}
		void setUniform2f(const char* const name,GLfloat vec0,GLfloat vec1)const
		{glUniform2f(glGetUniformLocation(programHandle,name),vec0,vec1);}
		void setUniform2f(const char* const name,const GLfloat* const vlePtr)const
		{glUniform2fv(glGetUniformLocation(programHandle,name),1,vlePtr);}
		void setUniform3f(const char* const name,GLfloat vec0,GLfloat vec1,GLfloat vec2)const
		{glUniform3f(glGetUniformLocation(programHandle,name),vec0,vec1,vec2);}
		void setUniform3f(const char* const name,const GLfloat* const vlePtr)const
		{glUniform3fv(glGetUniformLocation(programHandle,name),1,vlePtr);}
		void setUniform4f(const char* const name,GLfloat vec0,GLfloat vec1,GLfloat vec2,GLfloat vec3)const
		{glUniform4f(glGetUniformLocation(programHandle,name),vec0,vec1,vec2,vec3);}
		void setUniform4f(const char* const name,const GLfloat* const vlePtr)const
		{glUniform4fv(glGetUniformLocation(programHandle,name),1,vlePtr);}
		void setUniformMat2f(const char* const name,const GLfloat* const vlePtr, GLboolean transpose=GL_FALSE)const
		{glUniformMatrix2fv(glGetUniformLocation(programHandle,name),1,transpose,vlePtr);}
		void setUniformMat3f(const char* const name,const GLfloat* const vlePtr, GLboolean transpose=GL_FALSE)const
		{glUniformMatrix3fv(glGetUniformLocation(programHandle,name),1,transpose,vlePtr);}
		void setUniformMat4f(const char* const name,const GLfloat* const vlePtr, GLboolean transpose=GL_FALSE)const
		{glUniformMatrix4fv(glGetUniformLocation(programHandle,name),1,transpose,vlePtr);}

		void use()const
		{if(programHandle!=0){glUseProgram(programHandle);}}
		GLuint create()
		{
			programHandle=glCreateProgram();
			return programHandle;
		}
		
		void set(GLuint value){programHandle=value;}
		GLuint get()const{return programHandle;}
};

class Shader
{
	private:
		GLuint shaderHandle;
	public:
		Shader();
		explicit Shader(int);
		explicit Shader(const char* const,int);
		
		bool isZero()const{return shaderHandle==0;}
		int compile(const char* const)const;
		int compile(char** const)const;
		int compileStatus(bool print=false,const char* const path=0)const;
		int deleteStatus()const;
		int shaderType()const;
		void deletion()const{glDeleteShader(shaderHandle);}
		GLuint create(int mode)
		{
			shaderHandle=glCreateShader(mode);
			return shaderHandle;
		}
		
		void set(GLuint value){shaderHandle=value;}
		GLuint get()const{return shaderHandle;}
};

void activeBindTexture(GLuint,GLenum,GLuint);
void bindBufferData(GLenum,GLuint,GLsizeiptr,const GLvoid*,GLenum);
GLuint genBindBufferData(GLenum,GLsizeiptr,const GLvoid*,GLenum);

}

}
#endif

#ifdef CAP_GLSL_shader
namespace CAP
{

namespace GLSL
{
//Program
Program::Program():
	programHandle(0)
{}
Program::Program(GLuint ph):
	programHandle(ph)
{}

int Program::activeAttributes(bool print,const char* const path)const
{
	int location=0,maxLength=0,n=0,size=0,written=0,
		i=0;
	FILE *fp=0;
	GLenum type=0;
	
	glGetProgramiv(programHandle,GL_ACTIVE_ATTRIBUTES,&n);
	if(!print){return n;}
	if(n<=0){return n;}

	glGetProgramiv(programHandle,GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,&maxLength);
	std::vector<char> attribute(maxLength+1);
	attribute[maxLength]='\0';
	if(path==0){printf("location attribute written size type\n");}
	else
	{
		fopen_s(&fp,path,"ab");
		if(fp==0){return n;}
		
		fprintf(fp,"location attribute written size type\n");
	}
	for(i=0;i< n;i++)
	{
		glGetActiveAttrib(programHandle,i,maxLength,&written,&size,&type,&attribute[0]);
		location=glGetAttribLocation(programHandle,&attribute[0]);
		if(path==0){printf("%d %s %d %d %d\n", location,&attribute[0],written,size,type);}
		else{fprintf(fp,"%d %s %d %d %d\n", location,&attribute[0],written,size,type);}
	}
	
	if(path!=0){fclose(fp);}
	return n;
}
int Program::activeUniforms(bool print,const char* const path)const
{
	int location=0,maxLength=0,n=0,size=0,written=0,
		i=0;
	FILE *fp=0;
	GLenum type=0;
	
	glGetProgramiv(programHandle,GL_ACTIVE_UNIFORMS,&n);
	if(!print){return n;}
	if(n<=0){return n;}
	
	glGetProgramiv(programHandle,GL_ACTIVE_UNIFORM_MAX_LENGTH,&maxLength);
	std::vector<char> uniform(maxLength+1);
	uniform[maxLength]='\0';
	if(path==0){printf("location uniform written size type\n");}
	else
	{
		fopen_s(&fp,path,"ab");
		if(fp==0){return n;}
		
		fprintf(fp,"location uniform written size type\n");
	}
	for(i=0;i< n;i++)
	{
		glGetActiveUniform(programHandle,i,maxLength,&written,&size,&type,&uniform[0]);
		location=glGetUniformLocation(programHandle,&uniform[0]);
		if(path==0){printf("%d %s %d %d %d\n",location,&uniform[0],written,size,type);}
		else{fprintf(fp,"%d %s %d %d %d\n",location,&uniform[0],written,size,type);}
	}
	
	if(path!=0){fclose(fp);}
	return n;
}
int Program::attachedShaders()const
{
	int status=0;
	glGetProgramiv(programHandle,GL_ATTACHED_SHADERS,&status);
	return status;
}
int Program::deleteStatus()const
{
	int status=0;
	glGetProgramiv(programHandle,GL_DELETE_STATUS,&status);
	return status;
}
int Program::linkStatus(bool print,const char* const path)const
{
	int length=0,status=0,written=0;
	
	glGetProgramiv(programHandle,GL_LINK_STATUS,&status);
	if(status==GL_FALSE && print)
	{
		glGetProgramiv(programHandle,GL_INFO_LOG_LENGTH,&length);
		if(0< length)
		{
			std::vector<char> log(length+1);
			glGetProgramInfoLog(programHandle,length,&written,&log[0]);
			log[length]='\0';
			if(path==0){fprintf(stderr,"Program link log:\n%s\n", &log[0]);}
			else
			{
				CAP_appendFile(path,"Program link log:\n");
				CAP_appendFile(path,&log[0]);
				CAP_appendFile(path,"\n");
			}
		}
	}
	
	return status;
}
void Program::attachShader(const Shader& shader)const{glAttachShader(programHandle,shader.get());}
void Program::detachShader(const Shader& shader)const{glDetachShader(programHandle,shader.get());}

//Shader
Shader::Shader():
	shaderHandle(0)
{}
Shader::Shader(int mode):
	shaderHandle(glCreateShader(mode))
{}
Shader::Shader(const char* const path,int mode):
	shaderHandle(glCreateShader(mode))
{compile(path);}

int Shader::compile(const char* const path)const
{
	if(shaderHandle==0 || path==0){return 1;}
	
	char *codeArray[1]={CAP_readFile(path)};
	if(codeArray[0]==0){return 1;}
	
	glShaderSource(shaderHandle,1,codeArray,NULL);
	glCompileShader(shaderHandle);
	
	free(codeArray[0]);
	
	return 0;
}
int Shader::compile(char** const codeArray)const
{
	if(shaderHandle==0 || codeArray==0){return 1;}
	
	glShaderSource(shaderHandle,1,codeArray,NULL);
	glCompileShader(shaderHandle);
	
	return 0;
}
int Shader::compileStatus(bool print,const char* const path)const
{
	int length=0,status=0,written=0;
	
	glGetShaderiv(shaderHandle,GL_COMPILE_STATUS,&status);
	if(status==GL_FALSE && print)
	{
		glGetShaderiv(shaderHandle,GL_INFO_LOG_LENGTH,&length);
		if(0< length)
		{
			std::vector<char> log(length+1);
			glGetShaderInfoLog(shaderHandle,length,&written,&log[0]);
			log[length]='\0';
			if(path==0){fprintf(stderr,"Shader compile log:\n%s\n", &log[0]);}
			else
			{
				CAP_appendFile(path,"Shader compile log:\n");
				CAP_appendFile(path,&log[0]);
				CAP_appendFile(path,"\n");
			}
		}
	}
	
	return status;
}
int Shader::deleteStatus()const
{
	int status=0;
	glGetShaderiv(shaderHandle,GL_DELETE_STATUS,&status);
	return status;
}
int Shader::shaderType()const
{
	int status=0;
	glGetShaderiv(shaderHandle,GL_SHADER_TYPE,&status);
	return status;
}



//function
void activeBindTexture(GLuint textureN,GLenum target,GLuint textureID)
{
	glActiveTexture(GL_TEXTURE0+textureN);
	glBindTexture(target,textureID);
}
void bindBufferData(GLenum BUFFER_TARGET,GLuint buffers,GLsizeiptr size,const GLvoid* data,GLenum DATA_USAGE)
{
	glBindBuffer(BUFFER_TARGET,buffers);
	glBufferData(BUFFER_TARGET,size,data,DATA_USAGE);
}
GLuint genBindBufferData(GLenum BUFFER_TARGET,GLsizeiptr size,const GLvoid* data,GLenum DATA_USAGE)
{
	GLuint buffers;
	glGenBuffers(1,&buffers);
	bindBufferData(BUFFER_TARGET,buffers,size,data,DATA_USAGE);
	return buffers;
}

}

}
#endif
