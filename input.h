#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <array>
#include "vec2.h"

namespace Input {
	enum KeyState {
		Up, 
		Down,

		Changed = 4,
		ChangedUp = Changed|Up,
		ChangedDown = Changed|Down,
	};
	using ButtonState = KeyState;

	namespace {
		std::map<uint, KeyState> keys;
		std::array<ButtonState, 5> buttons;
		vec2 mousePos;
		vec2 mouseDelta;

		vec2 wheelDelta;
	}

	void ClearState();
	void NotifyKey(uint key, bool down);
	void NotifyMouseMove(int x, int y);
	void NotifyMouseButton(uint button, bool down);
	void NotifyMouseWheel(int dx, int dy);

	bool GetKey(uint key);
	bool GetKeyUp(uint key);
	bool GetKeyDown(uint key);

	bool GetButton(uint button);
	bool GetButtonUp(uint button);
	bool GetButtonDown(uint button);

	const vec2& GetMousePosition();
	const vec2& GetMouseDelta();
	const vec2& GetWheelDelta();
};

#endif