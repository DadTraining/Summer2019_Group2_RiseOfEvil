#include"Tower.h"
#define PI 3.14

void Tower::Init()
{
	m_sprite = Sprite::create("tower_demo.png");
}

Tower::Tower(Layer * layer)
{
	Init();
	for (int i = 0; i < 10; i++)
	{
		Bullet * bullet = new Bullet(layer);
		listBullet.push_back(bullet);
	}
	TMXTiledMap *mTileMap = TMXTiledMap::create("res/MapScene/Map01.tmx");
	auto obj = mTileMap->getObjectGroup("Monster");
	auto objTower = mTileMap->getObjectGroup("Tower");
	float tx = objTower->getObject("tower")["x"].asInt();
	float ty = objTower->getObject("tower")["y"].asInt();
	m_sprite->setPosition(tx, ty);
	m_sprite->setScale(0.5f);
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
