#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Crystal
{
private:
	Sprite *m_sprite;
	int m_hitpoint;
	int m_maxHitpoint;
	Sprite *hpBgSprite;
	ProgressTimer *hpBar;
public:
	Crystal(Layer *layer);
	~Crystal();
	void Init();
	void setPercentOfHealthBar();
	int getHitPoint();
	void setHitPoint(int hitPoint);
	Sprite* getSprite();
};