#pragma once

#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"

class Warrior : public Character
{
private:
	Animation* m_Animation;
	Rigidbody* m_Rigidbody;

public:
	Warrior(Properties* props);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
};

