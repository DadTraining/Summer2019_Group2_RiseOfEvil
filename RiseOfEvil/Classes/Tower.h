#pragma once
#include "Objects.h"
#include "cocos2d.h"
using namespace cocos2d;
class Tower :public Objects
{
private:
	int m_type;
	float m_attackSpeed;
	int m_range;
	//vector<Skill *>m_listSkill;
	//vector<Bullet *>m_listBullet;
	int m_level;
public:
	Tower(Scene *scene);
	~Tower();
	void Init(int type);
	void Update(float deltaTime);
	void Attack(Objects *);
	void Destroyed();
	void SetTarget(Objects *);
	void SetType(int);
	void SetAttackSpeed(float);
	void SetRange(int);
	//void SetListSkill(vector<Skill*>);
	//void SetListBullet(vector<Bullet*>);
	void SetLevel(int);
	int GetType();
	float GetAttackSpeed();
	int GetRange();
	//vector<Skill*> GetListSkill();
	//vector<Bullet*> GetListBullet();
	int GetLevel();
};