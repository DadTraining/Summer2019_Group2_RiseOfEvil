#pragma once
#include "cocos2d.h"
#include "Objects.h"
#define NORMAL_MONSTER 1
#define MAGICAN_MONSTER 2
#define TANK_MONSTER 3
#define SPEED_MONSTER 4
#define SIEGE_MONSTER 5
#define ELITE_MONSTER 6
#define DARKLORD  7
#define SLOW_SPEED 50
#define MEDIUM_SPEED 100
#define FAST_SPEED 150
using namespace cocos2d;
class Monster :public Objects
{
private:
	int m_type;
	float m_movementSpeed;
	float m_attackSpeed;
	int m_gold;
	//vector<Skill *>m_listSkill;
	int m_range;
	//Skill * speciall
public:
	Monster(Scene * scene, int type);
	~Monster();
	void Init();
	void Update(float deltaTime);
	void Move();
	void Acttack(Object *);
	void DoDead();
	void SetType(int type);
	void SetMovementSpeed(float);
	void SetAttackSpeed(float);
	void SetGold(int);
	void SetRange(int);
	int GetType();
	float GetMovementSpeed();
	float GetAttackSpeed();
	int GetGold();
	int GetRange();
};