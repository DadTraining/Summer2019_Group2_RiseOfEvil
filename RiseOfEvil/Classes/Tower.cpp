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
	layer->addChild(m_sprite, 3);
}

Sprite * Tower::GetSprite()
{
	return m_sprite;
}
int hp = 20;
void Tower::Shoot(float x, float y)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet.at(i)->GetSprite()->isVisible())
		{
			double degree = (atan((x - m_sprite->getPositionX()) / (y - m_sprite->getPositionY()))) * 180 / PI;
			log("Degree %d :%f",i ,degree);
			auto bullet = listBullet.at(i);
			bullet->GetSprite()->setVisible(true);
			bullet->GetSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY());
			auto rota = RotateTo::create(1.0f, degree);
			bullet->GetSprite()->runAction(rota);
			auto movetToOfBullet = MoveTo::create(1.0f, Vec2(x, y));
			auto callfunct = CallFunc::create(CC_CALLBACK_0(Tower::AfterShoot, this, bullet));
			//bullet->GetSprite()->setVisible(false);
			auto sq = Sequence::create(movetToOfBullet, callfunct, nullptr);
			bullet->GetSprite()->runAction(sq);
			break;
		}
	}
	hp -= 4;
}

void Tower::AfterShoot(Bullet * bullet)
{
	bullet->GetSprite()->setVisible(false);
}

void Tower::Update(float deltaTime, float x, float y)
{
	if (m_sprite->getPosition().getDistance(Vec2(x, y)) < range)
	{
		timeDelay += deltaTime;
		if (timeDelay > 1.0f)
		{
			Shoot(x, y);
			timeDelay = 0;
		}

	}
}

float Tower::DistanceRange(Sprite * m_sprite, float x, float y)
{
	return m_sprite->getPosition().getDistance(Vec2(x, y));
}
