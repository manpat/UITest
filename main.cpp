#include <iostream>

#include "debug.h"
#include "app.h"
#include "input.h"

int main(){
	try{
		if(!App::Init()) return 1;

		bool running = true;
		while(running){
			SDL_Event event;
			while(SDL_PollEvent(&event)){
				switch(event.type){
				case SDL_QUIT:
					running = false;
					break;

				case SDL_MOUSEMOTION:{
					auto& m = event.motion; 
					Input::NotifyMouseMove(m.x, m.y);
					break;
				}

				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:{
					auto& b = event.button;
					Input::NotifyMouseButton(b.button, b.state == SDL_PRESSED);
					break;
				}

				case SDL_MOUSEWHEEL:{
					auto& w = event.wheel;
					Input::NotifyMouseWheel(w.x, w.y);
					break;
				}

				case SDL_KEYDOWN:
				case SDL_KEYUP:
					if(event.key.keysym.sym == SDLK_ESCAPE) {
						running = false;
					}else{
						if(event.key.repeat == 0){
							Input::NotifyKey(event.key.keysym.sym, event.key.state == SDL_PRESSED);
						}
					}
					break;

				// default:
					// debug::log("Unknown event ", (void*)event.type);
				}
			}

			App::Update();
			App::Render();

			SDL_GL_SwapWindow(App::GetWindow());
			Input::ClearState();
		}

		App::Deinit();

	}catch(const char* e){
		debug::log("Error: ", e);
		return 1;
	}

	return 0;
}