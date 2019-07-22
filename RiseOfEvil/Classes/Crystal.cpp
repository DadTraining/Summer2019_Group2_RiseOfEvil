#include "Crystal.h"

Crystal::Crystal(Layer * layer)
{
	Init();
	layer->addChild(m_sprite, 3);
}

Crystal::~Crystal()
{
}

void Crystal::Init()
{
	m_sprite = Sprite::create("crystalBoss.png");
}

int Crystal::getHitPoint()
{
	return m_hitpoint;
}

void Crystal::setHitPoint(int hitPoint)
{
	m_hitpoint = hitPoint;
}

Sprite * Crystal::getSprite()
{
	return m_sprite;
}
