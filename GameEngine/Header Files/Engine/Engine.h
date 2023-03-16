#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"
 
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
private:
	Engine() { }
	bool m_IsRunning;
	static Engine* s_Instance;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	GameMap* m_LevelMap;

public :
	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}

	bool Init();
	bool Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }
};

