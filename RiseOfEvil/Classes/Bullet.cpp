#include "Bullet.h"
#include "Tower.h"

void Bullet::Init()
{
	bullet = Sprite::create("arrow.png");
}

Bullet::Bullet(Layer * layer)
{
	Init();
	bullet->setVisible(false);
	bullet->setScale(0.1f);
	bullet->setRotation(-75);
	//bullet->setPosition();
	layer->addChild(bullet, 5);
}

Sprite * Bullet::GetSprite()
{
	return bullet;
}

void Bullet::Disappear()
{
	bullet->removeFromParent();
}



