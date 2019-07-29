#pragma once
#include "cocos2d.h"
#include "Monster.h"
#include <iostream>
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
using namespace cocos2d;
using namespace std;
class Soldier :public Objects
{
private:
	int level;
	int m_maxHitPoint;
	int rangeOfSoldier = 50;
	float m_attackSpeed;
	float m_movementSpeed;
	float m_speed;
	float m_velocity;
	float timeMove = 0;
	int checkMove = 0;
	Layer * layer;
public:
	Soldier(Layer* layer, int level);
	~Soldier();
	void Init();
	void Update(float deltaTime);
	void MoveSoldier(Vec2 , bool, float, float);
	void Action(int, bool);
	void MoveToFlag(Vec2 Pos);
	Monster *FindNearestMonster(Monster *);
};
