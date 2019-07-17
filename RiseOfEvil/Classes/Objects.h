#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Objects
{
protected:
	int m_type;
	SpriteBatchNode *m_spriteNode;
	ProgressTimer *pBloodProGress;
	Sprite * m_sprite;
	Sprite * m_bloodBar;
	Sprite * m_blood;

	int m_hitPoint;
	int m_minimumAtk;
	int m_maximumAtk;
	int m_armor;

public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime);
	//virtual void Attack(Objects *target) = 0;

	void SetSprite(Sprite *);
	void SetHitPoint(int);
	void SetMinimumAtk(int);
	void SetMaximumAtk(int);
	void SetArmor(int);

	SpriteBatchNode * GetSpriteBatchNote();
	Sprite *GetSprite();
	int GetHitPoint();
	int GetMinimumAtk();
	int GetMaximumAtk();
	int GetArmor();

	Objects();
	~Objects();
};