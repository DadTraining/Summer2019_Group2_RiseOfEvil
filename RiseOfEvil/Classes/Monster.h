#pragma once
#include "cocos2d.h"
#include "Objects.h"
#define NORMAL 1
#define MAGICAN 2
#define TANK 3
#define SPEED 4
#define SIEGE 5
#define ELITE 6
#define DARKLORD 7
using namespace cocos2d;
class Monster :public Objects
{
private:
	int m_type;//type monster
	float m_movementSpeed;// speed monster
	float m_attackSpeed; // speed attack of monster
	int m_gold;
	//vector<Skill *>m_listSkill; list skill for monster
	int m_range; //range attack of monster
	//Skill * special; //skill special of monster
public:

	Monster(Scene * scene, int type);
	~Monster();
	void Init();
	void Update(float deltaTime);
	void Move();
	void Attack(Objects * target);
	void DoDead();

	void SetType(int type);
	void SetMovementSpeed(float movementSpeed);
	void SetAttackSpeed(float attackSpeed);
	void SetGold(int gold);
	void SetRange(int range);
	int GetType();
	float  GetMovementSpeed();
	float GetAttackSpeed();
	int GetGold();
	int GetRange();
};