#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Bullet
{
private:
	Sprite * bullet;
public:

	void Init();
	Bullet(Layer* layer);
	Sprite* GetSprite();
	void Disappear();
};