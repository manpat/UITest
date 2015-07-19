#include "debug.h"
#include "app.h"
#include "input.h"
#include "gfx.h"
#include "states.h"

namespace App {
	namespace {
		SDL_Window* window;
		SDL_GLContext glctx;

		gfx::Shader* shader;
		float aspect;
		vec2 aspectvec;
	}
	
	SDL_Window* GetWindow(){
		return window;
	}

	gfx::Shader* GetShader(){
		return shader;
	}

	float GetAspect(){
		return aspect;
	}

	const vec2& GetAspectVec(){
		return aspectvec;
	}

	void GLDebugFunc(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const char* message,
		GLvoid* userParam) {

		if(type == GL_DEBUG_TYPE_PERFORMANCE) return;

		switch(severity){
			case GL_DEBUG_SEVERITY_HIGH: debug::print("[high]"); break;
			case GL_DEBUG_SEVERITY_MEDIUM: debug::print("[medium]"); break;
			case GL_DEBUG_SEVERITY_LOW: debug::print("[low]"); break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: debug::print("[notification]"); break;
			default: debug::print("[unknown]");
		}

		debug::print("   src: ");

		switch(source){
			case GL_DEBUG_SOURCE_API: debug::print("API"); break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM: debug::print("WINDOW_SYSTEM"); break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: debug::print("SHADER_COMPILER"); break;
			case GL_DEBUG_SOURCE_THIRD_PARTY: debug::print("THIRD_PARTY"); break;
			case GL_DEBUG_SOURCE_APPLICATION: debug::print("APPLICATION"); break;
			case GL_DEBUG_SOURCE_OTHER: debug::print("OTHER"); break;
			default: debug::print("unknown");
		}

		debug::print("   type: ");

		switch(type){
			case GL_DEBUG_TYPE_ERROR: debug::print("error"); break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: debug::print("deprecated behaviour"); break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: debug::print("undefined behaviour"); break;
			case GL_DEBUG_TYPE_PORTABILITY: debug::print("portability issue"); break;
			case GL_DEBUG_TYPE_PERFORMANCE: debug::print("performance issue"); break;
			case GL_DEBUG_TYPE_MARKER: debug::print("marker"); break;
			case GL_DEBUG_TYPE_PUSH_GROUP: debug::print("push group"); break;
			case GL_DEBUG_TYPE_POP_GROUP: debug::print("pop group"); break;
			case GL_DEBUG_TYPE_OTHER: debug::print("other"); break;
			default: debug::print("unknown");
		}

		debug::log("\n\t", message);

	}

	bool Init(){
		if(SDL_Init(SDL_INIT_VIDEO) < 0){
			debug::log("SDL Init failed");
			return false;
		}

		window = SDL_CreateWindow("Blah", 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			Width, Height, 
			SDL_WINDOW_OPENGL);

		if(!window){
			debug::log("Window creation failed");
			return false;
		}

		constexpr bool debugContext = true;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, debugContext?SDL_GL_CONTEXT_DEBUG_FLAG:0);

		glctx = SDL_GL_CreateContext(window);
		if(!glctx){
			debug::log("OpenGL context creation failed");
			return false;
		}

		glewExperimental = true;
		if(auto e = glewInit()){
			debug::log("GLEW init failed");
			debug::log(glewGetErrorString(e));
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(&GLDebugFunc, nullptr);

		uint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		shader = new gfx::Shader("shader");
		aspect = Width/static_cast<float>(Height);
		aspectvec = vec2{aspect, 1};
		
		Action::InitSystem();

		debug::log("Init done");

		return true;
	}

	void Deinit(){
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}