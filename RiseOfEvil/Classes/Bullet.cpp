#include "Bullet.h"
#include "Tower.h"

void Bullet::Init()
{
	bullet = Sprite::create("bullet.png");
}

Bullet::Bullet(Layer * layer)
{
	Init();
	bullet->setVisible(false);
	bullet->setScale(0.03f);
	//bullet->setRotation(-75);
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



