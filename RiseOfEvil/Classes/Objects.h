#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Objects 
{
protected:
	int m_type;
	Sprite * m_sprite;
	int m_hitPoint;
	int m_minimumAtk;
	int m_maximumAtk;
	int m_armor;

public:
	virtual void Init(int type) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void Attack(Objects *target) = 0;

	void SetSprite(Sprite *);
	void SetHitPoint(int);
	void SetMinimumAtk(int);
	void SetMaximumAtk(int);
	void SetArmor(int);

	Sprite *GetSprite();
	int GetHitPoint();
	int GetMinimumAtk();
	int GetMaximumAtk();
	int GetArmor();

	Objects ();
	~Objects ();
};
