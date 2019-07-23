#pragma once
#include "cocos2d.h"
#include "Monster.h"
using namespace cocos2d;
class Soldier : public Objects
{
private:
	float timeDelay = 0;
	float m_movementSpeed = 20;
public:
	Soldier(Layer *);
	~Soldier();
	void Init();
	void Update(float deltaTime);
	void Move(Vec2);
	void AttackMonster(Monster*);
	float GetMovementSpeed();
	void SetMovementSpeed(float);
};
