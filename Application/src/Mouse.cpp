#include "Mouse.hpp"

#include "RenderWindow.hpp"

Mouse::Mouse(RenderWindow& renderWindow) : m_RenderWindow(renderWindow) {}

void Mouse::Update(SDL_Event& evnt) {
	memset(m_ButtonsDown, 0, MOUSE_BUTTON_COUNT);
	memset(m_ButtonsUp, 0, MOUSE_BUTTON_COUNT);

	m_ScrollDistance = 0.0f;

	if (evnt.button.button >= MOUSE_BUTTON_COUNT) return;

	else if (evnt.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		m_ButtonsDown[evnt.button.button] = true;
		m_ButtonStates[evnt.button.button] = true;
	}
	else if (evnt.type == SDL_EVENT_MOUSE_BUTTON_UP) {
		m_ButtonsUp[evnt.button.button] = true;
		m_ButtonStates[evnt.button.button] = false;
	}

	else if (evnt.type == SDL_EVENT_MOUSE_WHEEL) {
		m_ScrollDistance = evnt.wheel.y;
	}
}

bool Mouse::IsButtonDown(uint8_t button) {
	if (button >= MOUSE_BUTTON_COUNT) return false;
	return m_ButtonStates[button];
}

bool Mouse::IsButtonPressed(uint8_t button) {
	if (button >= MOUSE_BUTTON_COUNT) return false;
	return m_ButtonsDown[button];
}

bool Mouse::IsButtonReleased(uint8_t button) {
	if (button >= MOUSE_BUTTON_COUNT) return false;
	return m_ButtonsUp[button];
}

float Mouse::GetScrollDistance() {
	return m_ScrollDistance;
}

vec2 Mouse::GetPosition() {
	float x, y;
	SDL_GetMouseState(&x, &y);
	return vec2(x, y) / m_RenderWindow.GetSize();
}