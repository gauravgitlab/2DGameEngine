#pragma once

#include "Character.h"
#include "Animation.h"

class Warrior : public Character
{
private:
	Animation* m_Animation;

public:
	Warrior(Properties* props);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
};

