#pragma once

#include <SDL3/SDL.h>

#define KEY_COUNT 291

class TextInput;

class Keyboard {
public:
	Keyboard();

	void Update(SDL_Event& evnt);

	// returns the current state of the key
	bool IsKeyDown(SDL_Keycode keycode) const;

	// returns whether the key was pressed in the frame
	bool IsKeyPressed(SDL_Keycode keycode) const;

	// returns whether the key was released in the frame
	bool IsKeyReleased(SDL_Keycode keycode) const;

	bool IsShiftDown() const;

	bool IsControlDown() const;

	bool IsAltDown() const;

	bool IsAltGrDown() const;

	enum class Layout {
		Qwerty,
		Qwertz
	};

	friend class TextInput;

private:
	bool m_KeysDown[KEY_COUNT] = { false };
	bool m_KeysUp[KEY_COUNT] = { false };
	bool m_KeyStates[KEY_COUNT] = { false };

	bool m_CapsLock = false;

	Layout m_Layout;
};