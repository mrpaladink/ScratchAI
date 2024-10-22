#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <cmath>

Image::~Image() {
	if (m_Data) {
		stbi_image_free(m_Data);
	}
}

void Image::LoadFromFile(const char* path) {
	if (m_Data) {
		stbi_image_free(m_Data);
	}

	int32_t textureWidth = 0;
	int32_t textureHeight = 0;
	int32_t bitsPerPixel = 0;

	m_Data = (uint8_t*)stbi_load(path, &textureWidth, &textureHeight, &bitsPerPixel, 4);

	m_Size.width = abs(textureWidth);
	m_Size.height = abs(textureHeight);
}

void Image::LoadFromMemory(const char* data, size_t size) {
	if (m_Data) {
		stbi_image_free(m_Data);
	}

	int32_t textureWidth = 0;
	int32_t textureHeight = 0;
	int32_t bitsPerPixel = 0;

	m_Data = (uint8_t*)stbi_loadf_from_memory((const stbi_uc*)data, size, &textureWidth, &textureHeight, &bitsPerPixel, 4);

	m_Size.width = abs(textureWidth);
	m_Size.height = abs(textureHeight);
}