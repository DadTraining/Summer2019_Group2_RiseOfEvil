#pragma once
#include "cocos2d.h"
#include "Monster.h"
using namespace cocos2d;
class Bullet
{
private:
	Sprite * m_sprite;
public:

	void Init();
	Bullet(Layer* layer);
	void Update(float deltaTime);
	void Move(Monster*);
	void AfterShoot();
	Sprite* GetSprite();
	void Disappear();
};