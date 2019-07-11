//#include "Tower.h"
//#include "ResourceManager.h"
//Tower::Tower(Scene * scene, int type)
//{
//	m_type = type;
//	Init();
//	m_sprite->removeFromParent();
//	scene->addChild(m_sprite);
//}
//
//Tower::~Tower()
//{
//}
//
//void Tower::Init()
//{
//	switch (m_type)
//	{
//	case ARROW_TOWER:
//		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(ARROW_TOWER));//id = id of path arrow_tower 
//		m_hitPoint = 100;
//		m_minimumAtk = 4;
//		m_maximumAtk = 6;
//		m_armor = 0;
//		m_attackSpeed = 0.8;
//		m_range = 280;
//		m_cost = 70;
//		break;
//	case MAGIC_TOWER:
//		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(MAGIC_TOWER));//id = id of path MAGIC_TOWER 
//		m_hitPoint = 100;
//		m_minimumAtk = 9;
//		m_maximumAtk = 17;
//		m_armor = 0;
//		m_attackSpeed = 1.5;
//		m_range = 280;
//		m_cost = 100;
//		break;
//	case SLOW_TOWER:
//		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(SLOW_TOWER));//id = id of path SLOW_TOWER 
//		m_hitPoint = 100;
//		m_minimumAtk = 1;
//		m_maximumAtk = 3;
//		m_armor = 0;
//		m_attackSpeed = 1.3;
//		m_range = 180;
//		m_cost = 80;
//		break;
//	case BOMBARD_TOWER:
//		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(BOMBARD_TOWER));//id = id of path BOMBARD_TOWER 
//		m_hitPoint = 100;
//		m_minimumAtk = 10;
//		m_maximumAtk = 18;
//		m_armor = 0;
//		m_attackSpeed = 3.0;
//		m_range = 320;
//		m_cost = 125;
//		break;
//	case BARRACKS_TOWER:
//		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(BARRACKS_TOWER));//id = id of path BARRACKS_TOWER 
//		m_hitPoint = 100;
//		m_minimumAtk = 0;
//		m_maximumAtk = 0;
//		m_armor = 0;
//		m_attackSpeed = 0;
//		m_range = 180;
//		m_cost = 70;
//		break;
//	default:
//		break;
//	}
//}
//
//
//void Tower::Update(float deltaTime)
//{
//}
//
//void Tower::Attack(Objects *)
//{
//}
//
//void Tower::Destroyed()
//{
//}
//
//void Tower::SetTarget(Objects * target)
//{
//}
//
//void Tower::SetType(int type)
//{
//	m_type = type;
//}
//
//void Tower::SetAttackSpeed(float attackSpeed)
//{
//	m_attackSpeed = attackSpeed;
//}
//
//void Tower::SetRange(int range)
//{
//	m_range = range;
//}
//
//void Tower::SetCost(int cost)
//{
//	m_cost = cost;
//}
//
//void Tower::SetLevel(int level)
//{
//	m_level = level;
//}
//
//int Tower::GetType()
//{
//	return m_level;
//}
//
//float Tower::GetAttackSpeed()
//{
//	return m_attackSpeed;
//}
//
//int Tower::GetRange()
//{
//	return m_range;
//}
//
//int Tower::GetLevel()
//{
//	return m_level;
//}
//
//int Tower::GetCost()
//{
//	return m_cost;
//}
#include"Tower.h"

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
			auto bullet = listBullet.at(i);
			bullet->GetSprite()->setVisible(true);
			bullet->GetSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY());
			auto movetToOfBullet = MoveTo::create(0.2, Vec2(x, y));
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

int Tower::Update(float deltaTime, float x, float y)
{
	if (m_sprite->getPosition().getDistance(Vec2(x, y)) < range)
	{
		timeDelay += deltaTime;
		if (timeDelay > 0.5f)
		{
			Shoot(x, y);
			timeDelay = 0;
		}

	}
	if (hp == 0)
		return 1;
}

float Tower::DistanceRange(Sprite * m_sprite, float x, float y)
{
	return m_sprite->getPosition().getDistance(Vec2(x, y));
}
