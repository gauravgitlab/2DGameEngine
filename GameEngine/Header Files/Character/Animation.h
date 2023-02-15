#pragma once

#include <iostream>
#include "SDL.h"

class Animation
{
private:
	int m_SpriteRow, m_SpriteFrame;
	int m_AnimSpeed, m_FrameCount;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;

public:
	Animation() { } 

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

