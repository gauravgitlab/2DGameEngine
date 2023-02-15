#pragma once
#include "SDL.h"

class Input
{
private:
	Input();
	static Input* s_Instance;
	
	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates;

public:
	static Input* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	
};

