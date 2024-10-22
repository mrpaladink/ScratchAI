#include "RenderWindow.hpp"
#include "Texture.hpp"
#include "RenderElement.hpp"
#include "RenderElement.hpp"

#include <cstdio>

RenderWindow::RenderWindow(const char* name) : m_Mouse(*this) {
	m_Window = SDL_CreateWindow(name, 1240, 720, SDL_WINDOW_RESIZABLE);
	if (!m_Window) {
		exit(-1);
	}

	const char* renderDriver = nullptr;

	for (uint8_t i = 0; i < SDL_GetNumRenderDrivers(); i++) {
		if (strcmp(SDL_GetRenderDriver(i), "direct3d11") == 0) {						// default
			renderDriver = SDL_GetRenderDriver(i);
			break;
		}
		else if (strcmp(SDL_GetRenderDriver(i), "opengl") == 0 && !renderDriver) {		// second option
			renderDriver = SDL_GetRenderDriver(i);
			break;
		}
	}

	m_Renderer = SDL_CreateRenderer(m_Window, renderDriver);
	if (!m_Renderer) {
		exit(-1);
	}
}

RenderWindow::~RenderWindow() {
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}

void RenderWindow::Clear(const Color& color) {
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);

	SDL_RenderClear(m_Renderer);
}

void RenderWindow::Render(const Texture& texture, const FloatRect& rect, const UIntRect& area) {
	SDL_FRect srcRect = {
		area.x,
		area.y,
		area.w,
		area.h
	};

	SDL_FRect dstRect = {
		rect.x,
		rect.y,
		rect.w,
		rect.h
	};

	SDL_RenderTexture(m_Renderer, texture.m_Texture, srcRect.w == 0 || srcRect.h == 0 ? 0 : &srcRect, &dstRect);
}

void RenderWindow::Render(const Font& font, uint8_t alignment, const char* text, const FloatRect& rect, const UIntRect& area) {
	vec2 pos;
	pos.x = font.ComputeTargetPositionLineX(text, rect, alignment);
	pos.y = font.ComputeTargetPositionY(text, rect, alignment);

	for (size_t i = 0; text[i]; i++) {
		if (text[i] == '\n') {
			pos.y += font.m_Size;
			pos.x = font.ComputeTargetPositionLineX(&text[i + 1], rect, alignment);
			continue;
		}

		stbtt_aligned_quad q;
		stbtt_GetBakedQuad(font.m_BakedCharData, font.m_FontBitmapSize.w, font.m_FontBitmapSize.h, (unsigned char)text[i] - 32, &pos.x, &pos.y, &q, 0);

		SDL_FRect srcRect = {
			q.s0,
			q.t0,
			q.s1 - q.s0,
			q.t1 - q.t0
		};

		srcRect.x *= font.m_FontBitmapSize.w;
		srcRect.y *= font.m_FontBitmapSize.h;
		srcRect.w *= font.m_FontBitmapSize.w;
		srcRect.h *= font.m_FontBitmapSize.h;

		SDL_FRect dstRect = {
			q.x0,
			q.y0 + font.m_Size,
			q.x1 - q.x0,
			q.y1 - q.y0
		};

		SDL_RenderTexture(m_Renderer, font.m_FontBitmapTexture, &srcRect, &dstRect);

		/*SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
		SDL_RenderRect(m_Renderer, &dstRect);*/

		// sz = font.ComputeStringSize(text);
	}

	SDL_FRect dstRect2 = {
			rect.x,
			rect.y,
			rect.w,
			rect.h
	};

	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 255);
	SDL_RenderRect(m_Renderer, &dstRect2);
}

void RenderWindow::Render(const RenderBox& renderBox) {
	SDL_FRect dstRect = {
			renderBox.m_Rect.x,
			renderBox.m_Rect.y,
			renderBox.m_Rect.w,
			renderBox.m_Rect.h
	};

	SDL_SetRenderDrawColor(m_Renderer, renderBox.m_BackgroundColor.r, renderBox.m_BackgroundColor.g, renderBox.m_BackgroundColor.b, renderBox.m_BackgroundColor.a);
	SDL_RenderFillRect(m_Renderer, &dstRect);

	SDL_SetRenderDrawColor(m_Renderer, renderBox.m_OutlineColor.r, renderBox.m_OutlineColor.g, renderBox.m_OutlineColor.b, renderBox.m_OutlineColor.a);
	SDL_RenderRect(m_Renderer, &dstRect);

	for (auto& re : renderBox.m_RenderQueue) {
		
	}
}

void RenderWindow::Present() {
	SDL_RenderPresent(m_Renderer);
}

void RenderWindow::HandleEvent() {
	SDL_Event evt;
	SDL_WaitEvent(&evt);

	m_Keyboard.Update(evt);
	m_Mouse.Update(evt);

	switch (evt.type) {
	case SDL_EVENT_QUIT:
		m_IsClosed = true;
	}
}

bool RenderWindow::IsClosed() {
	return m_IsClosed;
}

Keyboard& RenderWindow::GetKeyboard() {
	return m_Keyboard;
}

Mouse& RenderWindow::GetMouse() {
	return m_Mouse;
}

vec2u RenderWindow::GetSize() {
	int x, y;
	SDL_GetWindowSize(m_Window, &x, &y);

	return vec2u(x, y);
}

vec2u RenderWindow::GetPosition() {
	int x, y;
	SDL_GetWindowPosition(m_Window, &x, &y);

	return vec2u(x, y);
}

UIntRect RenderWindow::GetRect() {
	return UIntRect(GetPosition(), GetSize());
}