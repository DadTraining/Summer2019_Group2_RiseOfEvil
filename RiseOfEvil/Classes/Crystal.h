#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Crystal
{
private:
	Sprite *m_sprite;
	int m_hitpoint;
	int m_maxHitpoint;
	Label *hitpointpercentLabel;
	Sprite *hpBgSprite;
	ProgressTimer *hpBar;
	ParticleFire *fire;
	bool crystalBurst = false;
	int count = 0;
	bool checkLose = false;
public:
	Crystal(Layer *layer);
	~Crystal();
	void Init();
	void setPercentOfHealthBar();
	int getHitPoint();
	void setHitPoint(int hitPoint);
	bool getcrystalBurst();
	bool getCheckLose();
	int getmaxHitPoint();
	Sprite* getSprite();
};