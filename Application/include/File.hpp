#pragma once

#include <cstdint>

class File {
public:
	File();

	File(const char* path);

	~File();

	void Read(const char* path);

	uint8_t* GetContent();

	size_t GetSize();

private:
	uint8_t* m_Content = nullptr;
	size_t m_Size = 0;
};