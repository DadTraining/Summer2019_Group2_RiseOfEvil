#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include <string>
#define NORMAL_MONSTER 1
#define MAGICAN_MONSTER 2
#define TANK_MONSTER 3
#define SPEED_MONSTER 4
#define SIEGE_MONSTER 5
#define ELITE_MONSTER 6
#define DARKLORD  7
#define SLOW_SPEED 50
#define MEDIUM_SPEED 50
#define FAST_SPEED 150
#define E  1
#define W  2
#define S  3
#define N  4
#define SE 5
#define NE 6
#define NW 7
#define SW 8
USING_NS_CC;
using namespace cocos2d;
using namespace std;
class Monster :public Objects
{
private:
	int m_type;
	int m_png[16];
	string m_fomatAnimation;
	float m_attackSpeed;
	int m_gold;
	int m_maxHitPoint;
	Animation *animation;
	float m_movementSpeed;
	float m_velocity;
	//vector<Skill *>m_listSkill;
	int m_range;
	Sprite * hp_bg;
	//Skill * speciall
public:
	int m_flag = 0;
	Monster(Layer*, int);
	~Monster();
	void Init();
	void Update(float deltaTime);
	void Move(Vec2);
	Animation* AnimationMonster(string, int, int, float);
	void Action(int);
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
	void setProgressBar();
	float GetVelocity();
};