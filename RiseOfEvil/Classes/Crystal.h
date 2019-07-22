#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Crystal
{
private:
	Sprite *m_sprite;
	int m_hitpoint;
public:
	Crystal(Layer *layer);
	~Crystal();
	void Init();
	int getHitPoint();
	void setHitPoint(int hitPoint);
	Sprite* getSprite();
};