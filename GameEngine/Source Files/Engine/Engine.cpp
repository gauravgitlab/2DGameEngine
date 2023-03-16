#include "Engine.h"
#include <iostream>
#include "TextureManager.h"
#include "Warrior.h"
#include "Input.h"
#include "SDL.h"
#include "Timer.h"
#include "MapParser.h"
#include <iostream>

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Failed to Initialize SDL : %s", SDL_GetError());
		return false;
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow("G-Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create windows : %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create renderer : %s", SDL_GetError());
		return false;
	}

	// load map
	if (MapParser::GetInstance()->Load()) {
		std::cout << "Successfully Load Map" << std::endl;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("level1");


	TextureManager::GetInstance()->Load("player", "Assets/Idle.png");
	TextureManager::GetInstance()->Load("player_run", "Assets/Run.png");

	player = new Warrior(new Properties("player", 100, 200, 128, 128));


	return m_IsRunning = true;
}

void Engine::Update()
{
	float deltaTime = Timer::GetInstance()->GetDeltaTime();

	m_LevelMap->Update(deltaTime);
	player->Update(deltaTime);
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
	SDL_RenderClear(m_Renderer);


	m_LevelMap->Render();

	//TextureManager::GetInstance()->Draw("player", 100, 100, 348, 436);
	player->Draw();

	SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}

void Engine::Quit()
{
	m_IsRunning = false;
}