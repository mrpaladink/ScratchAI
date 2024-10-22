#include "Keyboard.hpp"

#include <cstdlib>
#include <memory>

#ifdef WIN32 
#include <Windows.h>
#endif

Keyboard::Keyboard() {
	m_Layout = Layout::Qwerty;

#ifdef WIN32 
	HKL kb = GetKeyboardLayout(0);

	if (PRIMARYLANGID(LOWORD(GetKeyboardLayout(0))) == LANG_GERMAN) {
		m_Layout = Layout::Qwertz;
	}
#endif
}

void Keyboard::Update(SDL_Event& evnt) {
	memset(m_KeysDown, 0, KEY_COUNT);
	memset(m_KeysUp, 0, KEY_COUNT);

	SDL_Keycode code = evnt.key.scancode < KEY_COUNT ? evnt.key.scancode : 0;

	if (evnt.type == SDL_EVENT_KEY_DOWN) {
		m_KeysDown[code] = true;
		m_KeyStates[code] = true;
	}
	if (evnt.type == SDL_EVENT_KEY_UP) {
		m_KeysUp[code] = true;
		m_KeyStates[code] = false;
	}

	m_CapsLock = SDL_GetModState() & SDL_KMOD_CAPS;
}

bool Keyboard::IsKeyDown(SDL_Keycode keycode) const {
	return m_KeyStates[keycode < KEY_COUNT ? keycode : 0];
}

bool Keyboard::IsKeyPressed(SDL_Keycode keycode) const {
	return m_KeysDown[keycode < KEY_COUNT ? keycode : 0];
}

bool Keyboard::IsKeyReleased(SDL_Keycode keycode) const {
	return m_KeysUp[keycode < KEY_COUNT ? keycode : 0];
}

bool Keyboard::IsShiftDown() const {
	return m_KeyStates[SDL_SCANCODE_LSHIFT] || m_KeyStates[SDL_SCANCODE_RSHIFT] || m_CapsLock;
}

bool Keyboard::IsControlDown() const {
	return m_KeyStates[SDL_SCANCODE_LCTRL] || m_KeyStates[SDL_SCANCODE_RCTRL];
}

bool Keyboard::IsAltDown() const {
	return m_KeyStates[SDL_SCANCODE_LALT] || m_KeyStates[SDL_SCANCODE_RALT];
}

bool Keyboard::IsAltGrDown() const {
	return (IsAltDown() && IsControlDown()) || IsKeyDown(SDL_SCANCODE_RALT);
}