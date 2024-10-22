#include "TextInput.hpp"

#include "Keyboard.hpp"

#define DEFAULT_SHIFT_ALTGR(x, y, z) { if (shift) { return y; } else if (altgr) { return z; } else { return x; } }
#define DEFAULT_SHIFT(x, y) { if (shift) { return y; } else { return x; } }
#define DEFAULT_ALTGR(x, y) { if (altgr) { return y; } else { return x; } }
#define DEFAULT(x) { return x; }

TextInput::TextInput(Keyboard& keyboard) : 
	m_Keyboard(keyboard) {}

void TextInput::Update() {
	char input = 0;
	switch (m_Keyboard.m_Layout) {
	case Keyboard::Layout::Qwerty:
		input = GetQwerty();
		break;

	case Keyboard::Layout::Qwertz:
		input = GetQwertz();
		break;
	}

	if (input) {
		m_InputString += input;
	}
	else {
		if (m_Keyboard.IsKeyPressed(SDL_SCANCODE_BACKSPACE)) {
			if (m_InputString.size() > 0) m_InputString.pop_back();
		}
	}
}

const char* TextInput::GetString() {
	return m_InputString.c_str();
}

char TextInput::GetQwerty() {
	// TODO: Implementation
	for (uint16_t i = 0; i < KEY_COUNT; i++) {
		if (m_Keyboard.IsKeyPressed(i)) {
			if (i >= SDL_SCANCODE_A && i <= SDL_SCANCODE_Z) {
				uint16_t key = i;
				char baseKey = m_Keyboard.IsShiftDown() ? 'A' : 'a';
				return baseKey + key - SDL_SCANCODE_A;
			}
			else if (i >= SDL_SCANCODE_1 && i <= SDL_SCANCODE_9) {
				char baseKey = '1';
				return baseKey + i - SDL_SCANCODE_1;
			}
			else if (i == SDL_SCANCODE_0) {
				return '0';
			}
			else if (i == SDL_SCANCODE_SPACE) {
				return ' ';
			}
		}
	}

	return 0;
}

char TextInput::GetQwertz() {
	bool shift = m_Keyboard.IsShiftDown();
	bool altgr = m_Keyboard.IsAltGrDown();

	for (uint16_t i = 0; i < KEY_COUNT; i++) {
		if (m_Keyboard.IsKeyPressed(i)) {
			if (i >= SDL_SCANCODE_A && i <= SDL_SCANCODE_Z) {
				uint16_t key = i;
				if (key == SDL_SCANCODE_Y) {
					key = SDL_SCANCODE_Z;
				}
				else if (key == SDL_SCANCODE_Z) {
					key = SDL_SCANCODE_Y;
				}
				else if (key == SDL_SCANCODE_Q && altgr) {
					return '@';
				}
				char baseKey = shift ? 'A' : 'a';
				return baseKey + key - SDL_SCANCODE_A;
			}

			if (i >= SDL_SCANCODE_KP_1 && i <= SDL_SCANCODE_KP_9) {
				uint16_t key = i;
				char baseKey = '1';
				return '1' + key - SDL_SCANCODE_KP_1;
			}
			else if (i == SDL_SCANCODE_KP_0) {
				return '0';
			}

			switch (i) {
			case SDL_SCANCODE_1: DEFAULT_SHIFT('1', '!');
			case SDL_SCANCODE_2: DEFAULT_SHIFT_ALTGR('2', '"', '²');
			case SDL_SCANCODE_3: DEFAULT_SHIFT_ALTGR('3', '§', '³');
			case SDL_SCANCODE_4: DEFAULT_SHIFT('4', '$');
			case SDL_SCANCODE_5: DEFAULT_SHIFT('5', '%');
			case SDL_SCANCODE_6: DEFAULT_SHIFT('6', '&');
			case SDL_SCANCODE_7: DEFAULT_SHIFT_ALTGR('7', '/', '{');
			case SDL_SCANCODE_8: DEFAULT_SHIFT_ALTGR('8', '(', '[');
			case SDL_SCANCODE_9: DEFAULT_SHIFT_ALTGR('9', ')', ']');
			case SDL_SCANCODE_0: DEFAULT_SHIFT_ALTGR('0', '=', '}');
			case SDL_SCANCODE_MINUS: DEFAULT_SHIFT_ALTGR('ß', '?', '\\');
			case SDL_SCANCODE_SPACE: DEFAULT(' ');
			case SDL_SCANCODE_SEMICOLON: DEFAULT_SHIFT('ö', 'Ö');
			case SDL_SCANCODE_APOSTROPHE: DEFAULT_SHIFT('ä', 'Ä');
			case SDL_SCANCODE_LEFTBRACKET: DEFAULT_SHIFT('ü', 'Ü');
			case SDL_SCANCODE_COMMA: DEFAULT_SHIFT(',', ';');
			case SDL_SCANCODE_PERIOD: DEFAULT_SHIFT('.', ':');
			case SDL_SCANCODE_SLASH: DEFAULT_SHIFT('-', '_');
			case SDL_SCANCODE_NONUSBACKSLASH: DEFAULT_SHIFT_ALTGR('<', '>', '|');
			case SDL_SCANCODE_BACKSLASH: DEFAULT_SHIFT('#', '\'');
			case SDL_SCANCODE_EQUALS: DEFAULT_SHIFT('´', '`');
			case SDL_SCANCODE_GRAVE: DEFAULT_SHIFT('^', '°');
			case SDL_SCANCODE_KP_DIVIDE: DEFAULT('/');
			case SDL_SCANCODE_KP_MULTIPLY: DEFAULT('*');
			case SDL_SCANCODE_KP_MINUS: DEFAULT('-');
			case SDL_SCANCODE_KP_PLUS: DEFAULT('+');
			case SDL_SCANCODE_KP_PERIOD: DEFAULT(',');
			case SDL_SCANCODE_RETURN: DEFAULT('\n');
			}
		}
	}

	return 0;
}