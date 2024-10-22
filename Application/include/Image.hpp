#pragma once

#include <cstdint>
#include "Vector2.hpp"

class Texture;

class Image {
public:
	~Image();

	void LoadFromFile(const char* path);

	void LoadFromMemory(const char* data, size_t size);

	friend class Texture;

private:
	vec2u m_Size;
	uint8_t* m_Data = nullptr;
};