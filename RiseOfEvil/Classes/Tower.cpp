#include "Tower.h"
#include "ResourceManager.h"
Tower::Tower(Scene * scene)
{
}

Tower::~Tower()
{
}

void Tower::Init(int type)
{
	switch (type)
	{
	case 0:
		m_sprite =ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(0));
		break;

	default:
		break;
	}
}


void Tower::Update(float deltaTime)
{
}

void Tower::Attack(Objects *)
{
}

void Tower::Destroyed()
{
}

void Tower::SetTarget(Objects * target)
{
}

void Tower::SetType(int type)
{
	m_type = type;
}

void Tower::SetAttackSpeed(float attackSpeed)
{
	m_attackSpeed = attackSpeed;
}

void Tower::SetRange(int range)
{
	m_range = range;
}

void Tower::SetLevel(int level)
{
	m_level = level;
}

int Tower::GetType()
{
	return m_level;
}

float Tower::GetAttackSpeed()
{
	return m_attackSpeed;
}

int Tower::GetRange()
{
	return m_range;
}

int Tower::GetLevel()
{
	return m_level;
}
