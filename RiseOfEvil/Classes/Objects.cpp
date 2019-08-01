#include "Objects.h"


Objects::Objects()
{
}

Objects::~Objects()
{
}

void Objects::Update(float deltaTime)
{
}

void Objects::SetSprite(Sprite *sprite)
{
	m_sprite = sprite;
}

void Objects::SetHitPoint(int hitPoint)
{
	m_hitPoint = hitPoint;
}

void Objects::SetMinimumAtk(int miniumAtk)
{
	m_minimumAtk = miniumAtk;
}

void Objects::SetMaximumAtk(int maximumAtk)
{
	m_maximumAtk = maximumAtk;
}

void Objects::SetArmor(int armor)
{
	m_armor = armor;
}

SpriteBatchNode * Objects::GetSpriteBatchNote()
{
	return m_spriteNode;
}

Sprite * Objects::GetSprite()
{
	try
	{
		return m_sprite;
	}
	catch (...)
	{
		log("Sprite null !");
	}
	
}

int Objects::GetHitPoint()
{
	return m_hitPoint;
}

int Objects::GetMinimumAtk()
{
	return m_minimumAtk;
}

int Objects::GetMaximumAtk()
{
	return m_maximumAtk;
}

int Objects::GetArmor()
{
	return m_armor;
}