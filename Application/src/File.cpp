#include "File.hpp"

#include <cstdio>
#include <cstdlib>

File::File() {}

File::File(const char* path) {
	Read(path);
}

File::~File() {
	if (m_Content) {
		free(m_Content);
		m_Content = nullptr;
		m_Size = 0;
	}
}

void File::Read(const char* path) {
	if (m_Content) {
		free(m_Content);
		m_Content = nullptr;
		m_Size = 0;
	}

	FILE* f = fopen(path, "rb");

	fseek(f, 0, SEEK_END);
	m_Size = ftell(f);
	fseek(f, 0, SEEK_SET);

	m_Content = (uint8_t*)malloc(m_Size);
	fread(m_Content, m_Size, 1, f);

	fclose(f);
}

uint8_t* File::GetContent() {
	return m_Content;
}

size_t File::GetSize() {
	return m_Size;
}