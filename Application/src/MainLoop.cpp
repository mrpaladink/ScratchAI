#include "MainLoop.hpp"

#include <cstdio>
#include <SDL3/SDL.h>
#include <string>

#include "TextInput.hpp"
#include "Font.hpp"

MainLoop::MainLoop() :
	m_RenderWindow("Scratch AI") {
	SDL_Init(SDL_INIT_VIDEO);
}

MainLoop::~MainLoop() {
	SDL_Quit();
}

void MainLoop::Run() {
	Font font;
	font.Load(m_RenderWindow, "C:\\Windows\\Fonts\\CascadiaCode.ttf", 50.0f);

	Texture texture;
	texture.LoadFromFile(m_RenderWindow, "C:\\Users\\fabia\\Documents\\Random\\mario_sprites.png", UIntRect(0, 0, 16, 16));

	while (!m_RenderWindow.IsClosed()) {
		m_RenderWindow.HandleEvent();
		m_RenderWindow.Clear(Color(0, 0, 0, 255));

		static TextInput textInput(m_RenderWindow.GetKeyboard());
		textInput.Update();

		m_RenderWindow.Render(font, Font::Alignment::Center, textInput.GetString(), FloatRect(320, 160, 620, 360));
		
		m_RenderWindow.Present();
	}
}