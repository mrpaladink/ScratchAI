#pragma once

#include <cstdint>
#include <stb_truetype.h>
#include <SDL3/SDL.h>

#include "Vector2.hpp"
#include "Rect.hpp"

class RenderWindow;

class Font {
public:
	~Font();

	void Load(RenderWindow& renderWindow, const char* path, float size);

	friend class RenderWindow;

	enum Alignment {
		Left = 0x1,
		Right = 0x2,
		Top = 0x4,
		Bottom = 0x8,
		Center = 0x10
	};

private:
	vec2u ComputeBitmapSize(const unsigned char* data, int offset, float pixel_height, char first_char, int num_chars);

	float ComputeLineSize(const char* string) const;

	float ComputeStringSizeY(const char* string) const;

	float ComputeTargetPositionY(const char* string, FloatRect box, uint8_t alignment) const;

	float ComputeTargetPositionLineX(const char* string, FloatRect box, uint8_t alignment) const;

	SDL_Texture* m_FontBitmapTexture = nullptr;
	vec2u m_FontBitmapSize;
	stbtt_bakedchar* m_BakedCharData = nullptr;
	float m_Size = 0.0f;
};