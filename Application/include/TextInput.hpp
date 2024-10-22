#include "Keyboard.hpp"

#include <string>

class TextInput {
public:
	TextInput(Keyboard& keyboard);

	void Update();

	const char* GetString();

private:
	char GetQwerty();

	char GetQwertz();

	Keyboard& m_Keyboard;

	std::string m_InputString;
};