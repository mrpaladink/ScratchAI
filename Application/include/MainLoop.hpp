#pragma once

#include "RenderWindow.hpp"
#include "Texture.hpp"

class MainLoop {
public:
	MainLoop();

	~MainLoop();

	void Run();

private:
	RenderWindow m_RenderWindow;
};