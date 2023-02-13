#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"

Warrior::Warrior(Properties* props) : Character(props)
{
	m_Rigidbody = new Rigidbody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 8, 100);
}
void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
	m_Animation->SetProps("player", 1, 8, 100);
	m_Rigidbody->UnsetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		m_Rigidbody->ApplyForceX(4 * BACKWARD);
		m_Animation->SetProps("player_run", 1, 8, 100, SDL_FLIP_HORIZONTAL);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		m_Rigidbody->ApplyForceX(4 * FORWARD);
		m_Animation->SetProps("player_run", 1, 8, 100);
	}

	m_Rigidbody->Update(dt);
	
	m_Transform->TranslateX(m_Rigidbody->Position().X);
	//m_Transform->TranslateY(m_Rigidbody->Position().Y);

	m_Animation->Update();
}

void Warrior::Clean() 
{
	TextureManager::GetInstance()->Clean();
}
