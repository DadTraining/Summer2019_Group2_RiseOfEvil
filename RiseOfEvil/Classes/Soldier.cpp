#include "Soldier.h"

Soldier::Soldier(Layer * layer)
{
	Init();
	layer->addChild(m_Soldier,15);
}

Soldier::~Soldier()
{
}

void Soldier::Init()
{
	m_Soldier = Sprite::create("soldier.png");
	m_Soldier->setScale(0.2f);
}

void Soldier::Update(float deltaTime)
{
}

void Soldier::Move(Vec2 Pos)
{
	auto moveTo = MoveTo::create(0.5f, Pos);
	m_Soldier->runAction(moveTo);
}

Sprite * Soldier::GetSprite()
{
	return m_Soldier;
}
