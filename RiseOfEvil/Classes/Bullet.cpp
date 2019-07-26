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
	m_sprite->runAction(RepeatForever::create(RotateBy::create(0.05, 90)));
	m_sprite->runAction(sq);
}

void Bullet::AfterShoot()
{
	switch (bullet_type)
	{
		case ARROW_BULLET:
		{
			explotion_arrow = ParticleSystemQuad::create("explotion.plist");
			explotion_arrow->setVisible(true);
			explotion_arrow->setScale(0.7);
			explotion_arrow->setDuration(0.5);
			explotion_arrow->setPosition(m_sprite->getPosition());
			explotion_arrow->setAutoRemoveOnFinish(true);
			m_layer->addChild(explotion_arrow);
			break;
		}

		case MAGIC_BULLET:
		{
			auto explotion_magic = ParticleSun::create();
			explotion_magic->setPosition(m_sprite->getPosition());
			explotion_magic->setDuration(0.5);
			explotion_magic->setAutoRemoveOnFinish(true);
			m_layer->addChild(explotion_magic);
			break;
		}

		case SLOW_BULLET:
		{
			explotion_slow = ParticleSystemQuad::create("particle_magic.plist");
			explotion_slow->setVisible(true);
			explotion_slow->setScale(0.7);
			explotion_slow->setDuration(0.5);
			explotion_slow->setPosition(m_sprite->getPosition());
			explotion_slow->setAutoRemoveOnFinish(true);
			m_layer->addChild(explotion_slow);
			break;
		}

		case BOMBARD_BULLET:
		{
			auto explotion_boombard = ParticleSun::create();
			explotion_boombard->setPosition(m_sprite->getPosition());
			explotion_boombard->setDuration(0.5);
			explotion_boombard->setScale(2.5);
			explotion_boombard->setAutoRemoveOnFinish(true);
			m_layer->addChild(explotion_boombard);
			break;
		}
	}
	


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
