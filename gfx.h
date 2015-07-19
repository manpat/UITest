#ifndef GFX_H
#define GFX_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include "vec2.h"
#include "debug.h"

namespace gfx {
	struct Shader {
		Shader(const std::string&);
		void SetVec2(const std::string&, const vec2&);
		void SetFloat(const std::string&, float);
		void SetInt(const std::string&, int);

		uint sh;
	};

	struct VBO {
		VBO();
		~VBO();

		void Bind();
		static void Unbind();

		template<typename T>
		void Upload(const T* data, size_t cnt, uint usage = GL_STATIC_DRAW){
			glBufferData(GL_ARRAY_BUFFER, cnt*sizeof(T), data, usage);
			count = cnt;
		}
		template<typename T>
		void Upload(const std::vector<T>& data, uint usage = GL_STATIC_DRAW){
			glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(T), data.data(), usage);
			count = data.size();
		}

		void Draw(uint method = GL_TRIANGLES);

		uint buf;
		size_t count;
	};

}

#endif