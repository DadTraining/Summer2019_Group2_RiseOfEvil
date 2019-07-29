#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include "Crystal.h"
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
#define SW 6
#define NE 7
#define NW 8

USING_NS_CC;
using namespace cocos2d;
using namespace std;
class Monster :public Objects
{
private:
	int m_type;
	float rand;
	int m_png[32];
	string m_fomatAnimation;
	float m_attackSpeed;
	float m_runAnimation;
	float m_attackAnimation;
	int m_gold;
	int m_maxHitPoint;
	Animation *animation;
	float m_movementSpeed;
	float m_speed;
	float m_velocity;
	float speed; // 80% maxSpee
	float countToAttack = 0;
	Sprite * m_bloodBar;
	Sprite * m_blood;
	//vector<Skill *>m_listSkill;
	int m_range = 0;
	Sprite * hp_bg;
	Layer *layer;
	Sprite* dead1;
	Sprite* dead2;
	Sprite* dead3;
	//Skill * speciall
	int checkMove = 0;
	bool isSlow = false;
	float coutTimeToReduceHP = 0;
public:
	int m_flag = 0;
	Monster(Layer*, int);
	~Monster();
	void Init();
	void Update(float deltaTime);
	void Move(Vec2, bool, float, float);
	Animation* AnimationMonster(string, int, int, float);
	void Action(int, bool);
	void AttackCrystal(Crystal *,float);
	void DoDead();
	void SetType(int type);
	void SetMovementSpeed(float);
	void SetMSpeed(float);
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
	int GetCheckMove();
	bool GetIsSlow();
	void SetSlowRunSpeed();
	void SetIsSlow(bool);
	float GetMSpeed();
	int GetDamage();
	int GetMaxHitPoint();
	void ReduceHitPointMonster(int);
	bool IsDead();
};