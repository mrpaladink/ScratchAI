#pragma once

#include <SDL3/SDL.h>

#include "Vector2.hpp"

#define MOUSE_BUTTON_COUNT 3

class RenderWindow;

class Mouse {
public:
	Mouse(RenderWindow& renderWindow);

	void Update(SDL_Event& evnt);

	// returns the current state of the key
	bool IsButtonDown(uint8_t button);

	// returns whether the key was pressed in the frame
	bool IsButtonPressed(uint8_t button);

	// returns whether the key was released in the frame
	bool IsButtonReleased(uint8_t button);

	// returns a positive value for up and a negative value for down
	float GetScrollDistance();

	vec2 GetPosition();

private:
	bool m_ButtonsDown[MOUSE_BUTTON_COUNT] = { false };
	bool m_ButtonsUp[MOUSE_BUTTON_COUNT] = { false };
	bool m_ButtonStates[MOUSE_BUTTON_COUNT] = { false };

	float m_ScrollDistance = 0.0f;

	RenderWindow& m_RenderWindow;
};