#include <SDL2/SDL.h>
#include "input.h"
#include "debug.h"
#include "app.h"

namespace Input {
	void ClearState(){
		for(auto& kv: keys){
			kv.second = (KeyState)(kv.second & ~KeyState::Changed);
		}

		for(auto& b: buttons){
			b = (KeyState)(b & ~KeyState::Changed);
		}

		mouseDelta = {0,0};
		wheelDelta = {0,0};
	}

	void NotifyKey(uint key, bool down){
		keys[key] = down? KeyState::ChangedDown : KeyState::ChangedUp;
	}

	void NotifyMouseMove(int x, int y){
		vec2 m = {static_cast<float>(x*2), static_cast<float>(-y*2)};
		m /= vec2{App::Width, App::Height};
		m -= vec2{1,-1};

		mouseDelta += m - mousePos;
		mouseDelta.x *= 0.5;
		mouseDelta.y *= 0.5;
		mousePos = m;
	}

	void NotifyMouseButton(uint button, bool down){
		if(button > 5 || button == 0) return;

		auto state = down? KeyState::ChangedDown : KeyState::ChangedUp;
		buttons[button-1] = state;
	}

	void NotifyMouseWheel(int dx, int dy){
		wheelDelta = vec2{(float)dx, (float)dy};
	}

	bool GetKey(uint key){
		auto v = keys.find(key);
		if(v != keys.end()) return v->second & KeyState::Down;

		return false;
	}

	bool GetKeyUp(uint key){
		auto v = keys.find(key);
		if(v != keys.end()) return v->second == KeyState::ChangedUp;

		return false;
	}

	bool GetKeyDown(uint key){
		auto v = keys.find(key);
		if(v != keys.end()) return v->second == KeyState::ChangedDown;

		return false;
	}

	bool GetButton(uint b){
		if(b >= 5) return false;

		auto v = buttons[b];
		return v & ButtonState::Down;
	}

	bool GetButtonUp(uint b){
		if(b >= 5) return false;

		auto v = buttons[b];
		return v == ButtonState::ChangedUp;
	}

	bool GetButtonDown(uint b){
		if(b >= 5) return false;

		auto v = buttons[b];
		return v == ButtonState::ChangedDown;
	}

	const vec2& GetMousePosition(){
		return mousePos;
	}

	const vec2& GetMouseDelta(){
		return mouseDelta;
	}

	const vec2& GetWheelDelta(){
		return wheelDelta;
	}
}