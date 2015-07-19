#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace gfx { class Shader; }
struct vec2;

namespace App {
	enum {
		Width = 800,
		Height = 600,
	};

	bool Init();
	void Deinit();
	void Update();
	void Render();

	SDL_Window* GetWindow();
	gfx::Shader* GetShader();
	float GetAspect();
	const vec2& GetAspectVec();
}

#endif