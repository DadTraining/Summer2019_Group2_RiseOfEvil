#include"Tower.h"
#define PI 3.14

void Tower::Init()
{
	switch (m_type)
	{
	case ARROW_TOWER:
		m_sprite = Sprite::create("tower_demo.png");
		break;
	case MAGIC_TOWER:
		m_sprite = Sprite::create("tower_demo.png");
		break;
	case SLOW_TOWER:
		m_sprite = Sprite::create("tower_demo.png");
		break;
	case BOMBARD_TOWER:
		m_sprite = Sprite::create("tower_demo.png");
		break;
	case BARRACKS_TOWER:
		m_sprite = Sprite::create("tower_demo.png");
		break;
	}
}

Tower::Tower(Layer * layer, int type, Vec2 Pos)
{
	m_type = type;
	Init();
	for (int i = 0; i < 10; i++)
	{
		Bullet * bullet = new Bullet(layer);
		listBullet.push_back(bullet);
	}
	m_sprite->setScale(0.5f);
	m_sprite->setPosition(Pos);
	m_sprite->removeFromParent();
	layer->addChild(m_sprite, 5);
}

Sprite * Tower::GetSprite()
{
	return m_sprite;
}
int hp = 20;
void Tower::Shoot(Monster * monster)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet.at(i)->GetSprite()->isVisible())
		{
			listBullet.at(i)->GetSprite()->setVisible(true);
			listBullet.at(i)->GetSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY());
			listBullet.at(i)->Move(monster);
			break;
		}
	}
}

void Tower::Update(float deltaTime, Monster * monster)
{
	if (m_sprite->getPosition().getDistance(Vec2(monster->GetSprite()->getPositionX(), monster->GetSprite()->getPositionY())) < range)
	{
		timeDelay += deltaTime;
		if (timeDelay > 1.0f)
		{
			Shoot(monster);
			timeDelay = 0;
		}
	}
}

float Tower::GetRange()
{
	return range;
}
