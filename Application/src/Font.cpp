#include "Font.hpp"
#include "File.hpp"
#include "Image.hpp"

#include "RenderWindow.hpp"

#include <cstdio>
#include <cmath>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define FIRST_CHAR 32
#define CHAR_COUNT 256 - FIRST_CHAR

Font::~Font() {
	if (m_BakedCharData) {
		delete[] m_BakedCharData;
		m_BakedCharData = nullptr;

		SDL_DestroyTexture(m_FontBitmapTexture);
	}
}

vec2u Font::ComputeBitmapSize(const unsigned char* data, int offset, float pixel_height, char first_char, int num_chars) {
	float scale;
	int x, y, bottom_y, i;
	stbtt_fontinfo f;
	f.userdata = NULL;
	if (!stbtt_InitFont(&f, data, offset))
		return -1;
	x = y = 1;
	bottom_y = 1;
	
	scale = stbtt_ScaleForPixelHeight(&f, pixel_height);
	
	for (i = 0; i < num_chars; ++i) {
		int advance, lsb, x0, y0, x1, y1, gw, gh;
		int g = stbtt_FindGlyphIndex(&f, first_char + i);
		stbtt_GetGlyphHMetrics(&f, g, &advance, &lsb);
		stbtt_GetGlyphBitmapBox(&f, g, scale, scale, &x0, &y0, &x1, &y1);
		gw = x1 - x0;
		gh = y1 - y0;

		if (y + gh + 1 > bottom_y)
			bottom_y = y + gh + 1;
		
		x = x + gw + 1;
	}

	return vec2u(x + 1, bottom_y + 1);
}

void Font::Load(RenderWindow& renderWindow, const char* path, float size) {
	if (m_BakedCharData) {
		delete[] m_BakedCharData;
		m_BakedCharData = nullptr;

		SDL_DestroyTexture(m_FontBitmapTexture);
	}

	m_Size = size;

	File fontFile(path);
	m_FontBitmapSize = ComputeBitmapSize(fontFile.GetContent(), 0, size, FIRST_CHAR, CHAR_COUNT);
	uint8_t* fontBitmap = new uint8_t[m_FontBitmapSize.w * m_FontBitmapSize.h];
	m_BakedCharData = new stbtt_bakedchar[CHAR_COUNT];
	stbtt_BakeFontBitmap(fontFile.GetContent(), 0, size, fontBitmap, m_FontBitmapSize.w, m_FontBitmapSize.h, FIRST_CHAR, CHAR_COUNT, m_BakedCharData);

	uint32_t* fontBitmapRGBA = new uint32_t[m_FontBitmapSize.w * m_FontBitmapSize.h];
	for (uint64_t i = 0; i < m_FontBitmapSize.w * m_FontBitmapSize.h; i++) {
		fontBitmapRGBA[i] = fontBitmap[i];
		fontBitmapRGBA[i] |= 0xff000000;
	}
	delete[] fontBitmap;

	SDL_Surface* surface = SDL_CreateSurfaceFrom(m_FontBitmapSize.w, m_FontBitmapSize.h, SDL_PIXELFORMAT_RGBA8888, fontBitmapRGBA, m_FontBitmapSize.w * 4);
	m_FontBitmapTexture = SDL_CreateTextureFromSurface(renderWindow.m_Renderer, surface);
	SDL_SetTextureScaleMode(m_FontBitmapTexture, SDL_SCALEMODE_LINEAR);
	SDL_DestroySurface(surface);

	delete[] fontBitmapRGBA;
}

float Font::ComputeLineSize(const char* string) const {
	float pos1 = 0.0f, pos2 = 0.0f;

	float x = 0.0f, y = 0.0f;
	for (size_t i = 0; string[i] != '\n' && string[i] != '\0'; i++) {
		stbtt_aligned_quad q;
		stbtt_GetBakedQuad(m_BakedCharData, m_FontBitmapSize.w, m_FontBitmapSize.h, (unsigned char)string[i] - FIRST_CHAR, &x, &y, &q, 0);

		pos1 = std::min(q.x0, pos1);
		pos2 = std::max(q.x1, pos2);
	}

	float res = pos2 - pos1;

	return res;
}

float Font::ComputeStringSizeY(const char* string) const {
	size_t lineCount = 0;
	for (size_t i = 0; string[i]; i++) {
		if (string[i] == '\n') {
			lineCount++;
		}
	}

	return (lineCount + 1) * m_Size;
}

float Font::ComputeTargetPositionY(const char* string, FloatRect box, uint8_t alignment) const {
	float h = ComputeStringSizeY(string);

	if (alignment & Top) {
		return box.y;
	}
	else if (alignment & Center) {
		return box.y + box.h / 2.0f - h / 2.0f;
	}
	else if (alignment & Bottom) {
		return box.y + box.h - h;
	}
	else {
		return box.y;
	}
}

float Font::ComputeTargetPositionLineX(const char* string, FloatRect box, uint8_t alignment) const {
	vec2 line = ComputeLineSize(string);

	if (alignment & Left) {
		return box.x;
	}
	else if (alignment & Right) {
		return box.x + box.w - line.w;
	}
	else if (alignment & Center) {
		return box.x + box.w / 2.0f - line.w / 2.0f;
	}
	else {
		return box.x;
	}
}