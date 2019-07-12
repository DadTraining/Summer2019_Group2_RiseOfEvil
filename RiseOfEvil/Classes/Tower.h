#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Objects.h"
#include "Monster.h"
#include <iostream>

#define ARROW_TOWER 1
#define MAGIC_TOWER 2
#define SLOW_TOWER 3
#define BOMBARD_TOWER 4
#define BARRACKS_TOWER 5


using namespace std;
using namespace cocos2d;
class Tower : public Objects
{
private:
	//Sprite * tower;
	vector <Bullet *> listBullet;
	float range = 250;
public:
	void Init();
	Tower(Layer* layer);
	Sprite * GetSprite();
	void Shoot(Monster * monster);
	void AfterShoot(Bullet * bullet);
	void Update(float deltaTime, Monster* monster);
	float timeDelay = 0;
	float DistanceRange(Sprite * m_sprite, float x, float y);
	float GetRange();
};
//==================================
//#pragma once
//#include "Objects.h"
//#include "cocos2d.h"

//using namespace cocos2d;
//class Tower :public Objects
//{
//private:
//	int m_type;
//	float m_attackSpeed;
//	int m_range;
//	//vector<Skill *>m_listSkill;
//	//vector<Bullet *>m_listBullet;
//	int m_level;
//	int m_cost;
//	//Skill * special;
//public:
//	Tower(Scene *scene, int type);
//	~Tower();
//	void Init();
//	void Update(float deltaTime);
//	void Attack(Objects *);
//	void Destroyed();
//	void SetTarget(Objects *);
//	void SetType(int);
//	void SetAttackSpeed(float);
//	void SetRange(int);
//	void SetCost(int);
//	//void SetListSkill(vector<Skill*>);
//	//void SetListBullet(vector<Bullet*>);
//	void SetLevel(int);
//	int GetType();
//	float GetAttackSpeed();
//	int GetRange();
//	//vector<Skill*> GetListSkill();
//	//vector<Bullet*> GetListBullet();
//	int GetLevel();
//	int GetCost();
//
//};
//========================================================
