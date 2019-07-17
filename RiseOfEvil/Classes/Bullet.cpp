#include "Bullet.h"
#include "Tower.h"

void Bullet::Init()
{
	m_sprite = Sprite::create("bullet.png");
}

Bullet::Bullet(Layer * layer)
{
	Init();
	m_layer = layer;
	m_sprite->setVisible(false);
	m_sprite->setScale(0.03f);
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
	bezier.controlPoint_1 = Point(m_sprite->getPositionX(), m_sprite->getPositionY());
	bezier.controlPoint_2 = Point(Vec2(((m_sprite->getPositionX() + monster->GetSprite()->getPositionX()) / 2), (m_sprite->getPositionY() + monster->GetSprite()->getPositionY()) / 2 + 200));
	bezier.endPosition = Point(Vec2(monster->GetSprite()->getPositionX() + (0.4f * monster->GetVelocity()), monster->GetSprite()->getPositionY()));
	auto movetToOfBullet = BezierTo::create(0.4f, bezier);
	auto callfunct = CallFunc::create(CC_CALLBACK_0(Bullet::AfterShoot, this));
	auto sq = Sequence::create(movetToOfBullet, callfunct, nullptr);
	monster->setProgressBar();
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



