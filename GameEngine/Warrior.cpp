#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"

Warrior::Warrior(Properties* props) : Character(props)
{
	m_Rigidbody = new Rigidbody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 8, 100, SDL_FLIP_HORIZONTAL);
}
void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
	m_Rigidbody->Update(0.2);
	m_Transform->TranslateX(m_Rigidbody->Position().X);
	m_Transform->TranslateY(m_Rigidbody->Position().Y);

	m_Animation->Update();
}

void Warrior::Clean() 
{
	TextureManager::GetInstance()->Clean();
}
