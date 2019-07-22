#include "Bullet.h"
#include "Tower.h"

void Bullet::Init()
{
	switch (bullet_type)
		{
			case ARROW_BULLET:
				m_sprite = Sprite::create("darts.png");
				break;
			case MAGIC_BULLET:
				m_sprite = Sprite::create("bullet_magic.png");
				break;
			case SLOW_BULLET:
				m_sprite = Sprite::create("bullet_slow.png");
				break;
			case BOMBARD_BULLET:
				m_sprite = Sprite::create("bullet_boom.png");
				break;
			case BARRACKS_BULLET:
				m_sprite = Sprite::create("bullet_boom.png");
				break;
		}
}

Bullet::Bullet(Layer * layer, int type)
{
	bullet_type = type;
	Init();
	m_layer = layer;
	m_sprite->setVisible(false);
	m_sprite->setScale(0.3f);
	//bullet->setRotation(-75);
	//bullet->setPosition();
	layer->addChild(m_sprite, 5);
}

void Bullet::Update(float deltaTime)
{
	
}

void Bullet::Move(Monster * monster)
{
	ccBezierConfig bezier;
	//================Shoot Bezier=======================
	bezier.controlPoint_1 = Point(m_sprite->getPositionX(), m_sprite->getPositionY()+ 100);
	bezier.controlPoint_2 = Point(Vec2(((m_sprite->getPositionX() + monster->GetSprite()->getPositionX()) / 2), (m_sprite->getPositionY() + monster->GetSprite()->getPositionY()) / 2 + 200));
	if (monster->GetCheckMove() == 1)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() + (0.4 * monster->GetVelocity()), monster->GetSprite()->getPositionY()));
	}
	else if (monster->GetCheckMove() == 2)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() - (0.4 * monster->GetVelocity()), monster->GetSprite()->getPositionY()));
	}
	else if (monster->GetCheckMove() == 3)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX(), monster->GetSprite()->getPositionY() - (0.4 * monster->GetVelocity())));
	}
	else if (monster->GetCheckMove() == 4)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX(), monster->GetSprite()->getPositionY() + (0.4 * monster->GetVelocity())));
	}
	else if (monster->GetCheckMove() == 5)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() + (0.4 * monster->GetVelocity()), monster->GetSprite()->getPositionY() - (0.4 * monster->GetVelocity())));
	}
	else if (monster->GetCheckMove() == 6)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() - (0.4 * monster->GetVelocity()), monster->GetSprite()->getPositionY() - (0.4 * monster->GetVelocity())));
	}
	else if (monster->GetCheckMove() == 7)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() + (0.4 * monster->GetVelocity()), monster->GetSprite()->getPositionY() + (0.4 * monster->GetVelocity())));
	}
	else if (monster->GetCheckMove() == 8)
	{
		bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() - (0.4 * monster->GetVelocity()), monster->GetSprite()->getPositionY() + (0.4 * monster->GetVelocity())));
	}
	auto movetToOfBullet = BezierTo::create(0.4f, bezier);
	auto callfunct = CallFunc::create(CC_CALLBACK_0(Bullet::AfterShoot, this));
	auto sq = Sequence::create(movetToOfBullet, callfunct, nullptr);
	monster->setProgressBar();
	m_sprite->runAction(RepeatForever::create(RotateBy::create(0.05, 90)));
	m_sprite->runAction(sq);

}

void Bullet::AfterShoot()
{
	auto *expl = ParticleSystemQuad::create("explotion.plist");
	expl->setVisible(true);
	expl->setPosition(m_sprite->getPosition());
	m_layer->addChild(expl);
	m_sprite->setVisible(false);
}

Sprite * Bullet::GetSprite()
{
	return m_sprite;
}

void Bullet::Disappear()
{
	m_sprite->removeFromParent();
}



