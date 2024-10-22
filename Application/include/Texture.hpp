#pragma once

#include <SDL3/SDL.h>

#include "Image.hpp"
#include "Rect.hpp"

class RenderWindow;

class Texture {
public:
	~Texture();

	void LoadFromImage(RenderWindow& renderWindow, Image& image, UIntRect area = UIntRect());

	void LoadFromFile(RenderWindow& renderWindow, const char* file, UIntRect area = UIntRect());

	void LoadFromMemory(RenderWindow& renderWindow, const char* data, size_t size, UIntRect area = UIntRect());

	enum class ScaleMode {
		Linear,
		Nearest
	};

	void SetScaleMode(ScaleMode scaleMode);

	friend class RenderWindow;

private:
	uint8_t* GetNewImage(Image& image, UIntRect area);

	void LoadTexture(RenderWindow& renderWindow, Image& image, UIntRect area);

	SDL_Texture* m_Texture;
};