#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Soldier
{
private:
	int m_hitPoint;
	Sprite* m_Soldier;
	float timeDelay = 0;
public:
	Soldier(Layer *);
	~Soldier();
	void Init();
	void Update(float deltaTime);
	void Move(Vec2);
	Sprite * GetSprite();
};
