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
	ccBezierConfig bezier;
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet.at(i)->GetSprite()->isVisible())
		{
			auto bullet = listBullet.at(i);
			bullet->GetSprite()->setVisible(true);
			bullet->GetSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY());
			//================Shoot Bezier=======================
			bezier.controlPoint_1 = Point(listBullet[i]->GetSprite()->getPositionX(), listBullet[i]->GetSprite()->getPositionY());
			bezier.controlPoint_2 = Point(Vec2(((listBullet[i]->GetSprite()->getPositionX() + monster->GetSprite()->getPositionX()) / 2), (listBullet[i]->GetSprite()->getPositionY() + monster->GetSprite()->getPositionY()) / 2 + 200));

			bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() + (0.2 * monster->GetMovementSpeed()), monster->GetSprite()->getPositionY() + (0.2 * monster->GetMovementSpeed() )));
			auto movetToOfBullet = BezierTo::create(0.4f, bezier);

		//	auto movetToOfBullet = MoveTo::create(1.0f, Vec2(x, y));
			auto callfunct = CallFunc::create(CC_CALLBACK_0(Tower::AfterShoot, this, bullet));
			//bullet->GetSprite()->setVisible(false);
			auto sq = Sequence::create(movetToOfBullet, callfunct, nullptr);
			bullet->GetSprite()->runAction(sq);
			break;
		}
	}
}

void Tower::AfterShoot(Bullet * bullet)
{
	bullet->GetSprite()->setVisible(false);
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

float Tower::DistanceRange(Sprite * m_sprite, float x, float y)
{
	return m_sprite->getPosition().getDistance(Vec2(x, y));
}

float Tower::GetRange()
{
	return range;
}
