#pragma once
#include "cocos2d.h"
#include "Monster.h"
#include <iostream>
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define SOLDIERSPEED 80;
using namespace cocos2d;
using namespace std;
class Soldier : public Objects
{
private:
	Layer *layer;
	bool Dead = false;
	int direction = W;
	int m_type;
	float rand;
	int m_png[48];
	string m_fomatAnimation;
	float m_attackSpeed;
	float m_runAnimation;
	float m_attackAnimation;
	float m_guardAnimation;
	bool touchFlag = false;
	bool checkAttack = false;
	bool checkGuard = true;
	bool comeBack = false;
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
public:
	Soldier(Layer* layer);
	~Soldier();
	void Init();
	void Update(float deltaTime);
	void Move(Vec2);
	void MoveToMonster(Vec2, float);
	void Guard(float);
	Animation* AnimationMonster(string, int, int, float);

	void Action(int);
	void ActionMove(int);
	void ActionGuard(int);
	bool GetTouchFlag();
	void SetTouchFlag(bool);
	void SetTouchFlagTwo();
	void SetCheckAttack(bool);
	void StopAllAction();
	bool GetChecKGuard();
	void SetCheckGuard(bool);
	bool GetComeBack();
	void SetComeBack(bool);
	void SetComeBackTwo();
	int GetRange();
	void setProgressBar();
	int GetDamage();
	int GetMaxHitPoint();
	void ReduceHitPointSoldier(int);
	void SetRange(int);
	float GetMSpeed();
	float GetMovementSpeed();
	void SetMovementSpeed(float);
	bool IsDead();
	void Reborn();
	float GetAttackSpeed();
	void DoDead();
};
