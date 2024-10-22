#pragma once

#include <SDL3/SDL.h>

#include "Rect.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Font.hpp"
#include "RenderBox.hpp"

class Texture;

class RenderWindow {
public:
	RenderWindow(const char* name);

	~RenderWindow();

	void Clear(const Color& color = Color(0, 0, 0, 255));

	void Render(const Texture& texture, const FloatRect& rect, const UIntRect& area = UIntRect());

	void Render(const Font& font, uint8_t alignment, const char* text, const FloatRect& rect, const UIntRect& area = UIntRect());

	void Render(const RenderBox& renderBox);

	void Present();

	void HandleEvent();

	bool IsClosed();

	vec2u GetSize();

	vec2u GetPosition();

	UIntRect GetRect();

	Keyboard& GetKeyboard();

	Mouse& GetMouse();

	friend class Texture;

	friend class Font;

private:
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	Keyboard m_Keyboard;
	Mouse m_Mouse;

	bool m_IsClosed = false;
};