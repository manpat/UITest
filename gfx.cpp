#include "gfx.h"
#include "debug.h"

#include <vector>
#include <fstream>

namespace gfx {
	using std::string;

	Shader::Shader(const string& fname){
		std::vector<const char*> lines{"#version 330\n", "\n"}; 
		std::ifstream file(fname, std::ios::binary);
		if(!file) throw "Shader not found";

		file.seekg(0, file.end);
		auto length = file.tellg();
		file.seekg(0, file.beg);

		string data(length+1l, '\0');
		file.read(&data[0], length);
		lines.push_back(data.data());

		uint vsh, fsh;
		auto compileShader = [&](uint type) -> uint {
			auto sh = glCreateShader(type);

			switch(type){
			case GL_VERTEX_SHADER: lines[1] = "#define VS\n"; break;
			case GL_FRAGMENT_SHADER: lines[1] = "#define FS\n"; break;
			default: lines[1] = "";
			}

			glShaderSource(sh, lines.size(), lines.data(), nullptr);
			glCompileShader(sh);

			int status;
			glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
			if(status != GL_TRUE){
				char* buffer = new char[1024];
				glGetShaderInfoLog(sh, 1024, nullptr, buffer);

				debug::log(buffer);
				delete[] buffer;
				throw "Shader compile fail";
			}

			return sh;
		};

		vsh = compileShader(GL_VERTEX_SHADER);
		fsh = compileShader(GL_FRAGMENT_SHADER);

		sh = glCreateProgram();
		glAttachShader(sh, vsh);
		glAttachShader(sh, fsh);
		glLinkProgram(sh);

		glDeleteShader(vsh);
		glDeleteShader(fsh);

		int status;
		glGetProgramiv(sh, GL_LINK_STATUS, &status);
		if(status == GL_FALSE){
			int logLength = 0;
			glGetProgramiv(sh, GL_INFO_LOG_LENGTH, &logLength);

			char* buffer = new char[logLength];
			glGetProgramInfoLog(sh, logLength, nullptr, buffer);

			debug::log(buffer);
			throw "Program link fail";
		}

		glUseProgram(sh);
	}

	void Shader::SetVec2(const std::string& p, const vec2& v){
		auto loc = glGetUniformLocation(sh, p.data());
		if(loc < 0) throw "Uniform fuck";

		glUniform2fv(loc, 1, v.v);
	}
	void Shader::SetFloat(const std::string& p, float v){
		auto loc = glGetUniformLocation(sh, p.data());
		if(loc < 0) throw "Uniform fuck";

		glUniform1f(loc, v);
	}
	void Shader::SetInt(const std::string& p, int v){
		auto loc = glGetUniformLocation(sh, p.data());
		if(loc < 0) throw "Uniform fuck";

		glUniform1i(loc, v);
	}


	VBO::VBO(){
		glGenBuffers(1, &buf);
		count = 0;
	}
	VBO::~VBO(){
		glDeleteBuffers(1, &buf);
		buf = 0;
	}
	void VBO::Bind(){
		glBindBuffer(GL_ARRAY_BUFFER, buf);
	}
	void VBO::Unbind(){
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Draw(uint method){
		Bind();
		glVertexAttribPointer(0 /*pos*/, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(method, 0, count);
		Unbind();
	}
}