#pragma once
#include "cocos2d.h"
#include "Monster.h"
using namespace cocos2d;
using namespace std;
class Soldier : public Objects
{
private:
	int m_type;
	float rand;
	int m_png[32];
	string m_fomatAnimation;
	float m_attackSpeed;
	float m_runAnimation;
	float m_attackAnimation;
	bool touchFlag = true;
	bool checkFindMonster = false;
	vector<Monster*> m_listMonsterAttack;
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
	Soldier(Layer *);
	~Soldier();
	void Init();
	void Update(float deltaTime);
	void Move(Vec2);
	void MoveToMonster(Vec2, bool, float);
	Animation* AnimationMonster(string, int, int, float);

	void ActionMove(int);
	void Action(int, bool);
	void AttackMonster(Monster*);
	bool GetTouchFlag();
	void SetTouchFlag(bool);
	bool GetCheckFindMonster();
	void SetCheckFindMonster(bool);
	void SetTouchFlagTwo();
	vector<Monster*> GetListMonsterAttack();
	void SetListMonsterAttack(Monster*);
	float GetMSpeed();
	float GetMovementSpeed();
	void SetMovementSpeed(float);
};
