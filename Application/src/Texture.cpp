#include "Texture.hpp"
#include "RenderWindow.hpp"
#include "Rect.hpp"

#include <cstdio>

Texture::~Texture() {
	if (m_Texture) {
		SDL_DestroyTexture(m_Texture);
	}
}

uint8_t* Texture::GetNewImage(Image& image, UIntRect area) {
	uint8_t* buffer = new uint8_t[area.w * area.h * 4];

	for (uint32_t y = 0; y < image.m_Size.h; y++) {
		for (uint32_t x = 0; x < image.m_Size.w; x++) {
			if (y >= area.y && x >= area.x && y < area.y + area.h && x < area.x + area.w) {
				uint64_t i = (y * image.m_Size.w + x) * 4;

				uint64_t j = ((y - area.y) * area.w + x - area.x) * 4;

				buffer[j] = image.m_Data[i];
				buffer[j + 1] = image.m_Data[i + 1];
				buffer[j + 2] = image.m_Data[i + 2];
				buffer[j + 3] = image.m_Data[i + 3];
			}
		}
	}

	return buffer;
}

void Texture::LoadTexture(RenderWindow& renderWindow, Image& image, UIntRect area) {
	uint8_t* buffer = image.m_Data;
	vec2u size = image.m_Size;

	bool free = false;

	if (area.w && area.h && area.x + area.w <= image.m_Size.w && area.y + area.h <= image.m_Size.h) {
		buffer = GetNewImage(image, area);
		size = area.size;

		free = true;
	}

	if (m_Texture) {
		SDL_DestroyTexture(m_Texture);
	}

	SDL_Surface* surface = SDL_CreateSurfaceFrom(size.w, size.h, SDL_PIXELFORMAT_ABGR8888, buffer, size.w * 4);

	m_Texture = SDL_CreateTextureFromSurface(renderWindow.m_Renderer, surface);

	SDL_SetTextureScaleMode(m_Texture, SDL_SCALEMODE_NEAREST);

	SDL_DestroySurface(surface);

	if (free) delete[] buffer;
}

void Texture::LoadFromImage(RenderWindow& renderWindow, Image& image, UIntRect area) {
	LoadTexture(renderWindow, image, area);
}

void Texture::LoadFromFile(RenderWindow& renderWindow, const char* file, UIntRect area) {
	Image image;
	image.LoadFromFile(file);

	LoadTexture(renderWindow, image, area);
}

void Texture::LoadFromMemory(RenderWindow& renderWindow, const char* data, size_t length, UIntRect area) {
	Image image;
	image.LoadFromMemory(data, length);

	LoadTexture(renderWindow, image, area);
}

void Texture::SetScaleMode(ScaleMode scaleMode) {
	SDL_SetTextureScaleMode(m_Texture, scaleMode == ScaleMode::Linear ? SDL_SCALEMODE_LINEAR : SDL_SCALEMODE_NEAREST);
}