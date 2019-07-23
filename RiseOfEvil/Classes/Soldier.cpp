#include "Soldier.h"

Soldier::Soldier(Layer * layer)
{
	Init();
	m_sprite->removeFromParent(); 
	layer->addChild(m_sprite,15);
}

Soldier::~Soldier()
{
}

void Soldier::Init()
{
	m_sprite = Sprite::create("soldier.png");
	m_sprite->setScale(0.2f);
}

void Soldier::Update(float deltaTime)
{
}

void Soldier::Move(Vec2 Pos)
{
	auto moveTo = MoveTo::create(0.5f, Pos);
	m_sprite->runAction(moveTo);
}

void Soldier::AttackMonster(Monster * monster)
{
	auto moveTo1 = MoveTo::create(100 / m_movementSpeed, monster->GetSprite()->getPosition());
	auto moveTo2 = MoveTo::create(50 / m_movementSpeed, monster->GetSprite()->getPosition());
	if (m_sprite->getPosition().distance(monster->GetSprite()->getPosition()) <= 50)
	{
		m_movementSpeed = 0.00001;
		m_sprite->stopAction(moveTo1);
		m_sprite->runAction(moveTo2);
	}
	else if (m_sprite->getPosition().distance(monster->GetSprite()->getPosition()) <= 100)
	{		
		m_movementSpeed = 20;
		m_sprite->stopAction(moveTo2);
		m_sprite->runAction(moveTo1);
		
	}

}

float Soldier::GetMovementSpeed()
{
	return m_movementSpeed;
}

void Soldier::SetMovementSpeed(float movementSpeed)
{
	m_movementSpeed = movementSpeed;
}

